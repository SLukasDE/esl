/*
MIT License
Copyright (c) 2019 Sven Lukas

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

#ifndef ESL_UTILITY_OBJECTTIMEOUTPOOL_H_
#define ESL_UTILITY_OBJECTTIMEOUTPOOL_H_

#include <esl/Stacktrace.h>
#include <esl/logging/Logger.h>
#include <chrono>
#include <list>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>
#include <functional>
#include <stdexcept>

namespace esl {
namespace utility {

template<class Object>
class ObjectTimeoutPool {
	static esl::logging::Logger logger;
private:
	struct ObjectRelease {
		ObjectRelease(std::unique_ptr<Object> aObject, ObjectTimeoutPool<Object>& aObjectTimeoutPool)
		: object(std::move(aObject)),
		  objectTimeoutPool(&aObjectTimeoutPool)
		{
//			logger.debug << "ObjectRelease: constructor 1\n";
		}
		ObjectRelease() = default;
#if 0
		ObjectRelease() {
			logger.debug << "ObjectRelease: constructor 2\n";
		}

		ObjectRelease(const ObjectRelease& objectRelease)
		: objectTimeoutPool(objectRelease.objectTimeoutPool),
		  timePoint(objectRelease.timePoint)
		{
			logger.debug << "ObjectRelease: constructor 3 !!!!!!!!\n";
		}

		ObjectRelease(ObjectRelease&& objectRelease)
		: object(std::move(objectRelease.object)),
		  objectTimeoutPool(objectRelease.objectTimeoutPool),
		  timePoint(objectRelease.timePoint)
		{
			logger.debug << "ObjectRelease: constructor 4\n";
			objectRelease.objectTimeoutPool = nullptr;
		}

		~ObjectRelease() {
			logger.debug << "ObjectRelease: destructor\n";
		}
#endif
		void operator()(Object*) const {
			if(objectTimeoutPool) {
				logger.debug << "ObjectRelease: pool->release\n";
				objectTimeoutPool->release(*this);
			}
			else {
				logger.debug << "ObjectRelease: pool == nullptr\n";
			}
		}

		mutable std::unique_ptr<Object> object;
		ObjectTimeoutPool<Object>* objectTimeoutPool = nullptr;
		std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
	};
	friend struct ObjectRelease;

public:
	enum class Strategy {
		lifo, fifo
	};
	using CreateObject = std::function<std::unique_ptr<Object>()>;

	using unique_ptr = std::unique_ptr<Object, ObjectTimeoutPool<Object>::ObjectRelease>;

	ObjectTimeoutPool(unsigned int objectsMax, std::chrono::milliseconds timeout, CreateObject createObject, Strategy strategy, bool resetLifetimeOnGet, bool resetLifetimeOnRelease);
	~ObjectTimeoutPool();
	unique_ptr getObject();

private:
    void timeoutHandler();
    static bool isDirty(const Object& object);
    void release(const ObjectRelease& object);

    mutable ::std::mutex objectsMutex;
    std::condition_variable objectsCv;

    // number of objects in use
    unsigned int objectsMax;

    std::atomic_uint objectsCount;
    CreateObject createObject;
    Strategy strategy;
	bool resetLifetimeOnGet;
	bool resetLifetimeOnRelease;
    std::list<unique_ptr> objects;

    std::chrono::milliseconds timeout;
    bool timeoutHandlerExit = false;
    mutable std::mutex timeoutHandlerMutex;
    std::condition_variable timeoutHandlerCv;
    std::thread timeoutHandlerThread;
};


template<class Object>
esl::logging::Logger ObjectTimeoutPool<Object>::logger("esl::utility::ObjectTimeoutPool<>");


template<class Object>
ObjectTimeoutPool<Object>::ObjectTimeoutPool(unsigned int aObjectsMax, std::chrono::milliseconds aTimeout, CreateObject aCreateObject, Strategy aStrategy, bool aResetLifetimeOnGet, bool aResetLifetimeOnRelease)
: objectsMax(aObjectsMax),
  objectsCount(0),
  createObject(aCreateObject),
  strategy(aStrategy),
  resetLifetimeOnGet(aResetLifetimeOnGet),
  resetLifetimeOnRelease(aResetLifetimeOnRelease),
  timeout(aTimeout),
  timeoutHandlerThread(&ObjectTimeoutPool<Object>::timeoutHandler, this)
{
}

template<class Object>
ObjectTimeoutPool<Object>::~ObjectTimeoutPool() {
	{
		std::lock_guard<std::mutex> lockTimeoutHandlerMutex(timeoutHandlerMutex);
		std::lock_guard<std::mutex> lockObjectsMutex(objectsMutex);

		timeout = std::chrono::milliseconds(0);
		objectsMax = 0;
		objectsCv.notify_all();
		timeoutHandlerExit = true;
		timeoutHandlerCv.notify_one();
	}
	timeoutHandlerThread.join();
}
#if 0
/*
template<class Object>
void ObjectTimeoutPool<Object>::setMaxObjects(unsigned int maxObjects) {
	std::lock_guard<std::mutex> lock(objectsMutex);
	objectsMax = maxObjects;
	objectsCv.notify_all();
}
*/
void template<class Object>
unsigned int ObjectTimeoutPool<Object>::getMaxObjects() const {
	std::lock_guard<std::mutex> lock(objectsMutex);
	return objectsMax;
}

/*
template<class Object>
void ObjectTimeoutPool<Object>::setMaxTimeout(std::chrono::milliseconds aTimeout) {
	std::lock_guard<std::mutex> lock(timeoutHandlerMutex);
	maxIdleTime = aMaxIdleTime;
	timeoutHandlerCv.notify_all();
}
*/
template<class Object>
std::chrono::milliseconds ObjectTimeoutPool<Object>::getMaxTimeout() const {
	std::lock_guard<std::mutex> lock(timeoutHandlerMutex);
	return maxIdleTime;
}
#endif

template<class Object>
typename ObjectTimeoutPool<Object>::unique_ptr ObjectTimeoutPool<Object>::getObject() {
	logger.trace << "getObject (0)\n";
	{
		std::lock_guard<std::mutex> lockTimeoutHandlerMutex(timeoutHandlerMutex);

		if(timeoutHandlerExit) {
	    	throw esl::addStacktrace(std::runtime_error("object pool has been closed"));
		}
	}

	logger.trace << "getObject (1)\n";
	std::unique_lock<std::mutex> lockObjectsMutex(objectsMutex);

	logger.trace << "getObject (2)\n";
    while(objectsCount >= objectsMax) {
    	logger.trace << "getObject (3)\n";
    	objectsCv.wait(lockObjectsMutex);
    }

	logger.trace << "getObject (4)\n";
    /* delete outdated object */
// TODO: - Muesste hier nicht auch objectsCount reduziert werden?
//       - Und muesste dann die obige While-Schleife nicht danach kommen?
//       ( Nein?!, denn damit werden die Objekte gezaehlt, die im Umlauf sind )
	std::chrono::steady_clock::time_point timePointNow = std::chrono::steady_clock::now();
    std::chrono::milliseconds aTimeout = timeout;
	objects.remove_if([aTimeout, timePointNow](const unique_ptr& object) {
		return aTimeout == std::chrono::milliseconds(0) && object.get_deleter().timePoint + aTimeout <= timePointNow;
	});

	logger.trace << "getObject (5)\n";
	unique_ptr object;
	if(objects.empty()) {
		logger.trace << "getObject (5-1)\n";
        // create new object
    	std::unique_ptr<Object> objectOriginal = createObject();
    	Object* objectPtr = objectOriginal.get();
        object = unique_ptr(objectPtr, ObjectRelease(std::move(objectOriginal), *this));
	}
	else {
		if(strategy == Strategy::lifo) {
			logger.trace << "getObject (6-1)\n";
			object = std::move(objects.back());
			objects.pop_back();
		}
		else {
		// else if(strategy == Strategy::fifo) {
			logger.trace << "getObject (6-2)\n";
			object = std::move(objects.front());
			objects.pop_front();
		}

        // use existing object
		if(resetLifetimeOnGet) {
			object.get_deleter().timePoint = timePointNow;
		}
	}

	logger.trace << "getObject (7)\n";
    ++objectsCount;
    return object;

#if 0
	if(strategy == lifo) {
		for(auto iter = objects.rbegin(); iter != objects.rend() && !object; iter = objects.erase(iter)) {
			if(timeout == std::chrono::milliseconds(0) || iter->get_deleter().timePoint + timeout > timePointNow) {
				object = std::move(*iter);
			}
		}
	}
	else {
	// else if(strategy == fifo) {
		for(auto iter = objects.begin(); iter != objects.end() && !object; iter = objects.erase(iter)) {
			if(timeout == std::chrono::milliseconds(0) || iter->get_deleter().timePoint + timeout > timePointNow) {
				object = std::move(*iter);
			}
		}
	}

    if(object) {
        // use existing object
		if(renewLifetimeOnGet) {
			object.get_deleter().timePoint = timePointNow;
		}
    }
    else {
        // create new object
    	std::unique_ptr<Object> objectOriginal = createObject();
    	Object* objectPtr = objectOriginal.get();
        object = unique_ptr(objectPtr, ObjectRelease(std::move(objectOriginal), *this));
    }

    ++objectsCount;
    return object;
#endif
}

template<class Object>
void ObjectTimeoutPool<Object>::timeoutHandler() {
	std::unique_lock<std::mutex> lockTimeoutHandlerMutex(timeoutHandlerMutex);

    while(timeoutHandlerExit == false || objectsCount > 0) {
    	ESL__LOGGER(trace) << "timeoutHander() (1): objectsCount=" << objectsCount << "\n";
    	if(timeout == std::chrono::milliseconds(0)) {
    		ESL__LOGGER(trace) << "timeoutHander() (2): timeoutHandlerCv.wait(...)\n";
        	timeoutHandlerCv.wait(lockTimeoutHandlerMutex);
    	}
    	else {
    		ESL__LOGGER(trace) << "timeoutHander() (2): timeoutHandlerCv.wait_for(" << timeout.count() << "ms)\n";
        	timeoutHandlerCv.wait_for(lockTimeoutHandlerMutex, timeout);
    	}

    	ESL__LOGGER(trace) << "timeoutHander() (3)\n";
    	std::lock_guard<std::mutex> lockObjectsMutex(objectsMutex);
    	ESL__LOGGER(trace) << "timeoutHander() (4)\n";

        const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        for(auto iter = objects.begin(); iter != objects.end();) {
            if((timeout > std::chrono::milliseconds(0) && iter->get_deleter().timePoint + timeout < now) || isDirty(*iter->get())) {
            	ESL__LOGGER(trace) << "timeoutHander() (5): objects.erase(iter) (1)\n";
            	iter = objects.erase(iter);
                objectsCv.notify_one();
                ESL__LOGGER(trace) << "timeoutHander() (5): objects.erase(iter) (2)\n";
            } else {
            	ESL__LOGGER(trace) << "timeoutHander() (5): ++iter\n";
                ++iter;
            }
        }
        ESL__LOGGER(trace) << "timeoutHander() (6)\n";
    }
    ESL__LOGGER(trace) << "timeoutHander() (7): done\n";
}

template<class Object>
bool ObjectTimeoutPool<Object>::isDirty(const Object& object) {
	return false;
}

template<class Object>
void ObjectTimeoutPool<Object>::release(const ObjectRelease& objectRelease) {
	logger.trace << "release (0), objectsCount=" << objectsCount << "\n";
	std::unique_ptr<Object> objectOriginal(std::move(objectRelease.object));

	std::unique_lock<std::mutex> timeoutHandlerMutexLock(timeoutHandlerMutex);
	std::lock_guard<std::mutex> objectsMutexLock(objectsMutex);
	logger.trace << "release (1)\n";

    if((timeout > std::chrono::milliseconds(0) && objectRelease.timePoint + timeout < std::chrono::steady_clock::now())) {
    	logger.trace << "Drop timeout elapsed object.\n";
    }
    else if(isDirty(*objectOriginal.get())) {
    	logger.trace << "Drop dirty object.\n";
    }
    else {
    	logger.trace << "release (2)\n";
	    // renew Object
		Object* objectPtr = objectOriginal.get();
		unique_ptr object = unique_ptr(objectPtr, ObjectRelease(std::move(objectOriginal), *this));

		if(resetLifetimeOnRelease == false) {
			object.get_deleter().timePoint = objectRelease.timePoint;
		}

        objects.push_back(std::move(object));
    }

	--objectsCount;
	logger.trace << "release (3), objectsCount=" << objectsCount << "\n";
    objectsCv.notify_one();
    timeoutHandlerCv.notify_one();
	logger.trace << "release (4)\n";
}

} /* namespace utility */
} /* namespace esl */

#endif /* ESL_UTILITY_OBJECTTIMEOUTPOOL_H_ */
