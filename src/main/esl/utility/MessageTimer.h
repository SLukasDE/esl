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

#ifndef ESL_UTILITY_MESSAGETIMER_H_
#define ESL_UTILITY_MESSAGETIMER_H_

#include <list>
#include <chrono>
#include <memory>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <functional>
#include <atomic>

namespace esl {
namespace utility {

template<typename Key, typename Message>
class MessageTimer {
public:
	using MessageHandler = std::function<void(const Message&)>;

	MessageTimer(MessageHandler aMessageHandler)
    : messageHandler(aMessageHandler),
	  running(false)
    { }

    bool run();
    void stop();
	bool isRunning() const;

    /* add message with strong timepoint to occur */
    void addMessage(Key key, Message message, std::chrono::steady_clock::time_point timePoint);

    /* add message to occur in "timer" milliseconds and tell if timepoint is fixed or should be moved again if another message occurred */
    void addMessage(Key key, Message message, std::chrono::milliseconds timer, bool moveable, short priority = 0);

private:
    struct MessageType {
    	MessageType(Key aKey, Message aMessage, std::chrono::steady_clock::time_point aTimePoint)
    	: key(std::move(aKey)),
		  message(std::move(aMessage)),
		  movable(false),
		  priority(0),
		  timePoint(aTimePoint),
		  timer()
    	{
    		/*
    	    std::chrono::steady_clock::time_point timePointNow = std::chrono::steady_clock::now();
    	    if(timePoint < timePointNow) {
    	        timer = std::chrono::nanoseconds(0);
    	    }
    	    else {
    	        timer = timePoint - timePointNow;
    	    }
    		*/
    	}

    	MessageType(Key aKey, Message aMessage, std::chrono::milliseconds aTimer, bool aMovable, short aPriority)
    	: key(std::move(aKey)),
		  message(std::move(aMessage)),
		  movable(aMovable),
		  priority(aPriority),
		  timePoint(std::chrono::steady_clock::now() + aTimer),
		  timer(aTimer)
    	{
    	}

    	Key key;
    	Message message;
        bool movable;
        short priority;
        std::chrono::steady_clock::time_point timePoint;
        std::chrono::nanoseconds timer;
    };

    void addMessageType(MessageType messageType);

    MessageHandler messageHandler;
    std::atomic<bool> running;
    std::list<MessageType> messageTypes;

    /* set runThreadId to default value */
    std::thread::id runThreadId = std::thread::id();

    mutable std::mutex messageTypesMutex;
    mutable std::mutex newMessageMutex;
    std::condition_variable newMessage;
};

template<typename Key, typename Message>
bool MessageTimer<Key, Message>::run() {
	if(running.exchange(true) == true) {
		// already running
		return false;
	}
    runThreadId = std::this_thread::get_id();

	enum State {
	    noWait, // don't wait for anything, directly process messageTypes
	    wait,   // wait for notification to process messageTypes
	    waitFor // wait for notification or timeout to process messageTypes
	} state = noWait;

    std::unique_lock<std::mutex> lockNewMessage(newMessageMutex);
    std::chrono::nanoseconds timeout = std::chrono::seconds(0);

    while(true) {
    	/* check before wait because a message itself could have called stop().
    	 * In this case newMessage.notify() has no effect because there is no wait...(lockNewMessage) running to wakeup */
        if(running.load() == false) {
        	/* exit loop */
        	break;
        }

        switch(state) {
        case wait:
            newMessage.wait(lockNewMessage);
            break;
        case waitFor:
            newMessage.wait_for(lockNewMessage, timeout);
            break;
        default: // noWait
            break;
        }

        if(running.load() == false) {
        	/* exit loop */
        	break;
        }

        std::unique_ptr<Message> message;

        /* lock messageTypes */
        {
            std::lock_guard<std::mutex> lockMessageTypes(messageTypesMutex);

            /* find most urgent elapsed messageType */

    	    std::chrono::steady_clock::time_point timePointNow = std::chrono::steady_clock::now();
            auto iterMinTP = messageTypes.end();
            for(auto iter = messageTypes.begin(); iter != messageTypes.end(); ++iter) {
            	/* don't care about messages in future */
            	if(iter->timePoint > timePointNow) {
            		continue;
            	}

            	/* NOW WE ONLY INSPECT MESSAGES WITH ELAPSED TIME */

            	/* if we have not found any elapsed message so far, then take this message */
            	if(iterMinTP == messageTypes.end()) {
            		iterMinTP = iter;
            		continue;
            	}

            	/* ignore elapsed messages with lower priority */
            	if(iter->priority < iterMinTP->priority) {
            		continue;
            	}

            	/* take elapsed messages with higher priority */
            	if(iter->priority > iterMinTP->priority) {
            		iterMinTP = iter;
            		continue;
            	}

            	/* take messages if priority is the same but more urgent */
            	if(iter->timePoint < iterMinTP->timePoint) {
            		iterMinTP = iter;
            		continue;
            	}
            }

            /* remove found message and update moveable messages */
            if(iterMinTP != messageTypes.end()) {
            	/* remove found message */
                message.reset(new Message(std::move(iterMinTP->message)));
                messageTypes.erase(iterMinTP);

                /* reset movable messages */
                for(auto& messageType : messageTypes) {
                	if(messageType.movable) {
                		messageType.timePoint = timePointNow + messageType.timer;
                	}
                }
            }
        }

        /* now messageTypes is not locked anymore
         * Execute Message-Handler if message has been found */
        if(message) {
        	messageHandler(*message.get());
        	message.reset(nullptr);
        }

        /* lock messageTypes */
        {
            std::lock_guard<std::mutex> lockMessageTypes(messageTypesMutex);

            /* if there is no message in the queue, then set state to "wait" to block execution until a notification occurs. */
            if(messageTypes.empty()) {
            	/* no more messages in queue */
                state = wait;
                continue;
            }

            /* find most urgent message */
            auto iterMinTP = messageTypes.begin();
            for(auto iter = messageTypes.begin(); iter != messageTypes.end(); ++iter) {
            	if(iterMinTP == messageTypes.end() || iter->timePoint < iterMinTP->timePoint) {
            		iterMinTP = iter;
            	}
            }

    	    std::chrono::steady_clock::time_point timePointNow = std::chrono::steady_clock::now();
    	    /* if message has to occur in future, then set state to "waitFor" and set timeout to wait for. */
            if(iterMinTP->timePoint > timePointNow) {
            	/* next message is in future, set state to waitFor */
            	state = waitFor;
                timeout = iterMinTP->timePoint - timePointNow;
            }
    	    /* if message has to occurred already in the past, then set state to "noWait" to process next message immediately. */
            else {
            	/* next message occured already, set state to noWait */
                state = noWait;
            }

        }
    }

    /* reset runThreadId to default */
    runThreadId = std::thread::id();

    return true;
}

template<typename Key, typename Message>
void MessageTimer<Key, Message>::stop() {
    running.store(false);

	/* if function has been called from Thread running MessageTimer::run, then we can call addMessageType directly */
    if(runThreadId == std::this_thread::get_id()) {
        newMessage.notify_one();
    }
	/* if function has been called from external Thread, then we have to lock condition variable newMessage first */
    else {
        std::unique_lock<std::mutex> lockNewMessage(newMessageMutex);
        newMessage.notify_one();
    }
}

template<typename Key, typename Message>
bool MessageTimer<Key, Message>::isRunning() const {
    return running.load();
}

template<typename Key, typename Message>
void MessageTimer<Key, Message>::addMessage(Key key, Message message, std::chrono::steady_clock::time_point timePoint) {
	MessageType messageType(key, message, timePoint);

	/* if function has been called from Thread running MessageTimer::run, then we can call addMessageType directly */
    if(runThreadId == std::this_thread::get_id()) {
    	addMessageType(std::move(messageType));
    }
	/* if function has been called from external Thread, then we have to lock condition variable newMessage first */
    else {
        std::unique_lock<std::mutex> lockNewMessage(newMessageMutex);
    	addMessageType(std::move(messageType));
    }
}

template<typename Key, typename Message>
void MessageTimer<Key, Message>::addMessage(Key key, Message message, std::chrono::milliseconds timer, bool moveable, short priority) {
	MessageType messageType(key, message, timer, moveable, priority);

	/* if function has been called from Thread running MessageTimer::run, then we can call addMessageType directly */
    if(runThreadId == std::this_thread::get_id()) {
    	addMessageType(std::move(messageType));
    }
	/* if function has been called from external Thread, then we have to lock condition variable newMessage first */
    else {
        std::unique_lock<std::mutex> lockNewMessage(newMessageMutex);
    	addMessageType(std::move(messageType));
    }
}

template<typename Key, typename Message>
void MessageTimer<Key, Message>::addMessageType(MessageType messageType) {
    std::lock_guard<std::mutex> lockMessageTypes(messageTypesMutex);

    /* remove old message with same key first if there is a key specified */
    if(messageType.key != Key()) {
        for(auto iter = messageTypes.begin(); iter != messageTypes.end(); ++iter) {
            if(iter->key == messageType.key) {
                iter = messageTypes.erase(iter);
                break;
            }
        }
    }

	messageTypes.push_back(std::move(messageType));
    newMessage.notify_one();
}

} /* namespace utility */
} /* namespace esl */

#endif /* ESL_UTILITY_MESSAGETIMER_H_ */
