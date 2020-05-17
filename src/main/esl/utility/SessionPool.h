/*
MIT License
Copyright (c) 2019, 2020 Sven Lukas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef ESL_UTILITY_SESSIONPOOL_H_
#define ESL_UTILITY_SESSIONPOOL_H_

#include <esl/logging/Logger.h>
#include <chrono>
#include <map>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>

namespace esl {
namespace utility {

template<class Object, class Key, class CreateArgs>
class SessionPool {
	static esl::logging::Logger<> logger;

private:
	struct StoredObject {
		std::unique_ptr<Object> object;
		std::size_t circulating;
		std::chrono::steady_clock::time_point timePointBegin;
	};

	struct Deleter {
		static esl::logging::Logger<> logger;

		Deleter(SessionPool& aSessionPool, const Key& aKey)
		: sessionPool(&aSessionPool),
		  key(std::move(aKey))
		{ }
		Deleter() = default;

		void operator()(Object* object) const {
			if(object == nullptr) {
				ESL__LOGGER_ERROR_THIS("object == nullptr\n");
				return;
			}

			//std::unique_ptr<Object> objectPtr(object);
			ESL__LOGGER_DEBUG_THIS("object == ", object, "\n");

			if(sessionPool) {
				sessionPool->release(key);
				//sessionPool->release(std::move(objectPtr), timePointBegin);
			}
			else {
				ESL__LOGGER_DEBUG_THIS("objectPool has been detached\n");
			}
		}

		SessionPool* sessionPool = nullptr;
		const Key key;
	};

public:
	using CreateObject = std::function<std::unique_ptr<Object>(const CreateArgs& createArgs)>;
	using unique_ptr = std::unique_ptr<Object, Deleter>;

	/**
	 * Constructor
	 *
	 * @param[in] createObject Function object without arguments that returns unique_ptr<Object> to create an object for the pool
	 * @param[in] objectsMax Maximum amount of objects that the pool does allow.
	 *            A value of 0 means infinity number of objects.
	 * @param[in] objectLifetime Maximum lifetime of an object in this pool.
	 *                           A value of 0 means infinity lifetime.
	 * @param[in] resetLifetimeOnGet Specifies how lifetime of objects are handled if calling get(...).
	 *                               If this value is set to false the objects lifetime will not be touched when taking it out of the pool.
	 *                               If this value is set to true the objects lifetime will be reseted to its original lifetime when taking it out of the pool.
	 * @param[in] resetLifetimeOnRelease Specifies how lifetime of objects are handled when they are released back to the pool.
	 *                                   If this value is set to false the objects lifetime will not be touched when taking it back to the pool.
	 *                                   If this value is set to true the objects lifetime will be reseted to its original lifetime when taking it back to the pool.
	 */
	SessionPool(CreateObject createObject, size_t objectsMax, std::chrono::nanoseconds objectLifetime, bool resetLifetimeOnGet, bool resetLifetimeOnRelease);
	~SessionPool();

	/**
	 * Returns a object from object pool. If maximum number of objects are circulating already outside this pool, then this function will wait.
	 * If a timeout>0 is specified, it will return not later than this time but it will return an empty object (nullptr) if there is still no
	 * more space free for getting an object.
	 * If ObjectPool gets destroyed this function will also return immediately with an empty object (nullptr).
	 *
	 * @param[in] timeout Duration to wait for getting an object. A value of 0 means no wait.
	 * @param[in] strategy Specifies which object is returned form the pool, if no new object has to be created.
	 *                     If strategy is set to Strategy::lifo, then the object that has been latest released back to the pool is returned.
	 *                     If stratefy is set to Strategy::lifo, then the object will be returned that is remaining longest time in the pool.
	 */
	unique_ptr get(const Key& key, const CreateArgs& createArgs, std::chrono::nanoseconds timeout);
	unique_ptr get(const Key& key, const CreateArgs& createArgs);

private:
    void timeoutHandler();
	void release(const Key& key);
//	void release(std::unique_ptr<Object> object, std::chrono::steady_clock::time_point timePointBegin);
	bool checkGetObject() const;
	bool isTimeoutOrDirty(const Object& object, std::chrono::steady_clock::time_point timePointBegin, std::chrono::steady_clock::time_point timePointNow) const;
    static bool isDirty(const Object& object);

	const CreateObject createObject;
	const size_t objectsMax;

	/* objectLifetime==0 means infinity lifetime.
	 * A real lifetime of zero would make no sense, because
	 * the object would be invalid directly after creating it.
	 */
	const std::chrono::nanoseconds objectLifetime;
	const bool resetLifetimeOnGet;
	const bool resetLifetimeOnRelease;

    mutable std::mutex objectsMutex;
    std::condition_variable objectsCv;
    std::condition_variable objectsTimeoutHandlerCv;
    //std::list<unique_ptr> objects;
    std::map<Key, StoredObject> objects;

    /* number of objects that are retrieved by calling get()
     * and not put back to the pool so far.
     */
	std::size_t objectsCirculating{0};
    bool descructorCalled{false};

    std::thread timeoutHandlerThread;
};

template<class Object, class Key, class CreateArgs>
esl::logging::Logger<> SessionPool<Object, Key, CreateArgs>::logger("esl::utility::SessionPool<>");

template<class Object, class Key, class CreateArgs>
esl::logging::Logger<> SessionPool<Object, Key, CreateArgs>::Deleter::logger("esl::utility::SessionPool<>::Deleter");

template<class Object, class Key, class CreateArgs>
SessionPool<Object, Key, CreateArgs>::SessionPool(CreateObject aCreateObject, size_t aObjectsMax, std::chrono::nanoseconds aObjectLifetime, bool aResetLifetimeOnGet, bool aResetLifetimeOnRelease)
: createObject(aCreateObject),
  objectsMax(aObjectsMax),
  objectLifetime(aObjectLifetime),
  resetLifetimeOnGet(aResetLifetimeOnGet),
  resetLifetimeOnRelease(aResetLifetimeOnRelease)
{
	/* if objectLifetime is zero, then objects have infinity lifetime and we don't need a thread to delete expired objects */
	if(objectLifetime != std::chrono::nanoseconds(0)) {
		  timeoutHandlerThread = std::thread(&SessionPool::timeoutHandler, this);
	}
}

template<class Object, class Key, class CreateArgs>
SessionPool<Object, Key, CreateArgs>::~SessionPool() {
	{
    	std::lock_guard<std::mutex> objectsMutexLock(objectsMutex);
    	descructorCalled = true;
	}

	if(objectLifetime != std::chrono::nanoseconds(0)) {
		/* Notify timeout handler to delete all objects in the pool.
		 * Timeout handler will call "objectsCv.notify_all();" then
		 * to let waiting get-Calls returning an empty object.
		 * Timeout handler will still wait till all circling objects
		 * outside this pool are released. */
		objectsTimeoutHandlerCv.notify_one();

		/* let's wait till timeout handler is done */
		ESL__LOGGER_TRACE_THIS("before \"timeoutHandlerThread.join()\"\n");
		timeoutHandlerThread.join();
		ESL__LOGGER_TRACE_THIS("after \"timeoutHandlerThread.join()\"\n");
	}
	else {
		/* There is no thread running.
		 * So we notify all waiting get-Calls directly to return a nullptr.
		 */
		objectsCv.notify_all();
	}
}

template<class Object, class Key, class CreateArgs>
typename SessionPool<Object, Key, CreateArgs>::unique_ptr SessionPool<Object, Key, CreateArgs>::get(const Key& key, const CreateArgs& createArgs) {
	return get(key, createArgs, std::chrono::nanoseconds(0));
}

template<class Object, class Key, class CreateArgs>
typename SessionPool<Object, Key, CreateArgs>::unique_ptr SessionPool<Object, Key, CreateArgs>::get(const Key& key, const CreateArgs& createArgs, std::chrono::nanoseconds timeout) {
	ESL__LOGGER_TRACE_THIS("before lock\n");
	std::unique_lock<std::mutex> objectsMutexLock(objectsMutex);
	ESL__LOGGER_TRACE_THIS("after lock\n");

	// objectsMax == 0 means infinity number of objects, so we don't need to wait
	if(objectsMax > 0) {
    	if(timeout == std::chrono::nanoseconds(0)) {
    		objectsCv.wait(objectsMutexLock, std::bind(&SessionPool::checkGetObject, this));
    	}
    	else if(!objectsCv.wait_for(objectsMutexLock, timeout, std::bind(&SessionPool::checkGetObject, this))) {
    		ESL__LOGGER_DEBUG_THIS("timeout\n");
			return unique_ptr(nullptr, Deleter(*this, std::chrono::steady_clock::time_point{}));
    	}
	}

	if(descructorCalled) {
		ESL__LOGGER_TRACE_THIS("descructor called, return nullptr\n");
		return unique_ptr(nullptr, Deleter(*this, std::chrono::steady_clock::time_point{}));
	}

	ESL__LOGGER_TRACE_THIS("++objectsCirculating\n");
    ++objectsCirculating;

	//if(objects.empty()) {
	auto iter = objects.find(key);
	if(iter == objects.end()) {
		ESL__LOGGER_TRACE_THIS("createObject()\n");

		// create new object
		//std::unique_ptr<Object> object = createObject();
		//return unique_ptr(object.release(), Deleter(*this, std::chrono::steady_clock::now()));
		StoredObject storedObject;
		storedObject.object = createObject(createArgs);
		storedObject.circulating = 1;
		storedObject.timePointBegin = std::chrono::steady_clock::now();

		Object* objectPtr = storedObject.object.get();

		objects.insert(std::make_pair(key, storedObject));
		return unique_ptr(objectPtr, Deleter(*this, key));
	}


	++iter->second.circulating;
	/*
	unique_ptr object;
	if(strategy == Strategy::lifo) {
		ESL__LOGGER_TRACE_THIS("LIFO\n");
		object = std::move(objects.back());
		objects.pop_back();
	}
	else {
	// else if(strategy == Strategy::fifo) {
		ESL__LOGGER_TRACE_THIS("FIFO\n");
		object = std::move(objects.front());
		objects.pop_front();
	}

    // use existing object
	if(resetLifetimeOnGet) {
		ESL__LOGGER_TRACE_THIS("resetLifetimeOnGet\n");
		//object.get_deleter().timePointBegin = std::chrono::steady_clock::now();
		iter->second.timePointBegin = std::chrono::steady_clock::now();
	}

	return object;
	*/
	return unique_ptr(iter->second.object.get(), Deleter(*this, key));
}

template<class Object, class Key, class CreateArgs>
void SessionPool<Object, Key, CreateArgs>::timeoutHandler() {
	std::unique_lock<std::mutex> objectsMutexLock(objectsMutex);
	std::chrono::steady_clock::time_point timePointNow = std::chrono::steady_clock::now();

    while(descructorCalled == false || objectsCirculating > 0) {
		ESL__LOGGER_TRACE_THIS("calculate timeoutHandlerWakeup\n");
		std::chrono::nanoseconds timeoutHandlerWakeup{0};
		for(const auto& object : objects) {
    		if(object->second.timePointBegin + objectLifetime <= timePointNow) {
    			continue;
    		}
			std::chrono::nanoseconds remainingLifetime;
			remainingLifetime = std::chrono::duration_cast<std::chrono::nanoseconds>(object->second.timePointBegin + objectLifetime - timePointNow);
			if(timeoutHandlerWakeup > remainingLifetime || timeoutHandlerWakeup == std::chrono::nanoseconds(0)) {
				timeoutHandlerWakeup = remainingLifetime;
			}
		}
		ESL__LOGGER_DEBUG_THIS("timeoutHandlerWakeup = ", timeoutHandlerWakeup.count(), "ns\n");

    	if(timeoutHandlerWakeup == std::chrono::nanoseconds(0)) {
    		ESL__LOGGER_TRACE_THIS("timeoutHandlerCv.wait()\n");
    		objectsTimeoutHandlerCv.wait(objectsMutexLock);
    	}
    	else {
    		ESL__LOGGER_TRACE_THIS("timeoutHandlerCv.wait_for(", timeoutHandlerWakeup.count(), "ns)\n");
    		objectsTimeoutHandlerCv.wait_for(objectsMutexLock, timeoutHandlerWakeup);
    	}

		ESL__LOGGER_TRACE_THIS("delete elapsed objects\n");
    	timePointNow = std::chrono::steady_clock::now();
        for(auto iter = objects.begin(); iter != objects.end();) {
        	if(descructorCalled || isTimeoutOrDirty(*iter->second.object, iter->second.timePointBegin, timePointNow)) {
        		// prevent Deleter to call "SessionPool::release"
        		iter->get_deleter().objectPool = nullptr;

        		ESL__LOGGER_DEBUG_THIS("erase object = ", iter->get(), "\n");
        		iter = objects.erase(iter);
        	}
        	else {
        		++iter;
        	}
        }
        objectsCv.notify_all();
    }
	ESL__LOGGER_TRACE_THIS("RETURN\n");
}

template<class Object, class Key, class CreateArgs>
void SessionPool<Object, Key, CreateArgs>::release(const Key& key) {
//void SessionPool<Object, Key, CreateArgs>::release(std::unique_ptr<Object> object, std::chrono::steady_clock::time_point timePointBegin) {
	/*
	if(!object) {
		ESL__LOGGER_ERROR_THIS("called with nullptr object\n");
		return;
	}
	*/

	ESL__LOGGER_TRACE_THIS("before lock\n");
	std::lock_guard<std::mutex> objectsMutexLock(objectsMutex);
	ESL__LOGGER_TRACE_THIS("after lock\n");

	auto iter = objects.find(key);
	if(iter == objects.end()) {
		ESL__LOGGER_ERROR_THIS("called with nullptr object\n");
		return;
	}

	--iter->second.circulating;

	if(descructorCalled) {
    	ESL__LOGGER_DEBUG_THIS("Destroy object because ~ObjectPool() has been called.\n");
	}
	else if(iter->second.circulating == 0) {
//	else {
		std::chrono::steady_clock::time_point timePointNow = std::chrono::steady_clock::now();

		if(!iter->second.object || isTimeoutOrDirty(*iter->second.object, iter->second.timePointBegin, timePointNow)) {
	    	ESL__LOGGER_DEBUG_THIS("Destroy object because timeout occurred or object is dirty.\n");
	    	objects.erase(iter);
	    }
	    else {
    	    // renew Object
    		if(resetLifetimeOnRelease) {
    			ESL__LOGGER_TRACE_THIS("resetLifetimeOnRelease\n");
    			iter->second.timePointBegin = timePointNow;
    		}

	    	//ESL__LOGGER_DEBUG_THIS("objects.emplace_back(...) with object=", object.get(), "\n");
    		//objects.emplace_back(unique_ptr(object.release(), Deleter(*this, timePointBegin)));
        }
	}

	--objectsCirculating;
    /* notify to let's get a new object or to if in exit-mode to return nullptr */
    objectsCv.notify_one();

	if(objectLifetime != std::chrono::nanoseconds(0)) {
	    /* notify to calulate new wait time or if in exit-mode to check if objectsCirculating == 0 */
		objectsTimeoutHandlerCv.notify_one();
	}
}

template<class Object, class Key, class CreateArgs>
bool SessionPool<Object, Key, CreateArgs>::checkGetObject() const {
	return descructorCalled || objectsMax == 0 || objectsMax > objectsCirculating;
}

template<class Object, class Key, class CreateArgs>
bool SessionPool<Object, Key, CreateArgs>::isTimeoutOrDirty(const Object& object, std::chrono::steady_clock::time_point timePointBegin, std::chrono::steady_clock::time_point timePointNow) const {
    return (objectLifetime > std::chrono::nanoseconds(0) && timePointBegin + objectLifetime <= timePointNow) || isDirty(object);
}

template<class Object, class Key, class CreateArgs>
bool SessionPool<Object, Key, CreateArgs>::isDirty(const Object& object) {
	return false;
}

} /* namespace utility */
} /* namespace esl */

#endif /* ESL_UTILITY_SESSIONPOOL_H_ */
