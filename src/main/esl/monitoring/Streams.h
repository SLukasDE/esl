/*
MIT License
Copyright (c) 2019-2025 Sven Lukas

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

#ifndef ESL_MONITORING_STREAMS_H_
#define ESL_MONITORING_STREAMS_H_

#include <esl/monitoring/OStream.h>

#include <chrono>
#include <cstring>
#include <memory>
#include <ostream>
#include <thread>

namespace esl {
inline namespace v1_6 {
namespace monitoring {

class Logging;

class Streams {
public:
	enum class Level {
		trace,
		debug,
		info,
		warn,
		error,
		silent
	};

	class Real;

	class Writer {
	friend class Streams::Real;
	public:
		Writer(const Writer&) = delete;

		Writer& operator=(const Writer&) = delete;
		Writer& operator=(Writer&&) = delete;

		template<typename T>
		inline Writer& operator<<(const T& t) {
			if(oStream && oStream->getOStream()) {
				*oStream->getOStream() << t;
			}
			return *this;
		}

		Writer& operator<<(std::ostream& (*pf)(std::ostream&));

	    template<typename T>
		inline Writer& write(const T& t) {
			if(oStream && oStream->getOStream()) {
				*oStream->getOStream() << t;
			}
			return *this;
		}

	    template<typename T, typename... Args>
		inline Writer& write(const T& t, Args... args) {
			if(oStream && oStream->getOStream()) {
				*oStream->getOStream() << t;
				return write(args...);
			}
			return *this;
		}


	private:
		Writer(std::unique_ptr<OStream> oStream);
		Writer(Writer&& streamWriter);

	    std::unique_ptr<OStream> oStream;
	};

	class Real {
	public:
		Real(const char* typeName, Level level);

	    Writer operator()(const void* object);
	    Writer operator()(const char* function, const char* file, unsigned int lineNo);
	    Writer operator()(const void* object, const char* function, const char* file, unsigned int lineNo);

		template<typename T>
		inline Writer operator<<(const T& t) {
	        Writer writer(getWriter(nullptr, nullptr, nullptr, 0));
	        writer << t;
	        return writer;
		}

	    Writer operator<<(std::ostream& (*pf)(std::ostream&));

	    const char* getTypeName() const {
	    	return typeName;
	    }

		Level getLevel() const {
			return level;
		}

		explicit operator bool() const;

	private:
	    Writer getWriter(const void* object, const char* function, const char* file, unsigned int lineNo);

	    const char* typeName;
		Level level;
		Logging* logging = nullptr;
	};

	class Empty {
	public:
		Empty() = default;

	    inline Empty& operator()(const void*) {
			return *this;
	    }
	    inline Empty& operator()(const char*, const char*, unsigned int) {
			return *this;
	    }
	    inline Empty& operator()(const void*, const char*, const char*, unsigned int) {
			return *this;
	    }

		template<typename T>
		inline Empty& operator<<(const T& t) {
			return *this;
		}

	    inline Empty& operator<<(std::ostream& (*pf)(std::ostream&)) {
	    	return *this;
	    }

	    inline constexpr explicit operator bool() const noexcept {
	    	return false;
	    }

	    /* deprecated: use "operator bool()" instead */
		inline constexpr bool isEnabled() const {
			return false;
		}
	};

    template<typename... Args>
	static inline void write(Real& streamReal, const void* object, const char* function, const char* file, unsigned int lineNo, Args... args) {
    	streamReal(object, function, file, lineNo).write(args...);
    }

    template<typename... Args>
	static inline void write(Empty& streamEmpty, const void* object, const char* function, const char* file, unsigned int lineNo, Args... args) {
    }

    class Location {
    public:
    	Location() = default;

    	Location(Level level, const void* object, const char* typeName, const char* function, const char* file, std::size_t line, std::thread::id threadId)
    	: level(level),
    	  object(object),
    	  typeName(typeName),
    	  function(function),
    	  file(file),
    	  line(line),
    	  threadId(threadId)
    	{ }

    	inline bool operator==(const Location& location) const {
    		return timestamp == location.timestamp &&
    				level == location.level &&
    				object == location.object &&
    				stringEqual(typeName, location.typeName) &&
    				stringEqual(function, location.function) &&
    				stringEqual(file, location.file) &&
    				line == location.line &&
    				threadId == location.threadId;
    	}

    	inline bool operator!=(const Location& location) const {
    		return !(*this == location);
    	}

    	std::chrono::time_point<std::chrono::system_clock> timestamp = std::chrono::system_clock::now();
    	Level level = Level::silent;
    	const void* object = nullptr;
    	const char* typeName = nullptr;
    	const char* function = nullptr;
    	const char* file = nullptr;
    	std::size_t line = 0;
    	std::thread::id threadId = std::this_thread::get_id();

    	// this is just an additional payload and has no effect to constructor, comperator etc.
    	bool enabled = true;

    private:
    	inline static int stringCmp(const char* s1, const char* s2) {
    		if(s1 == nullptr) {
    			return s2 == nullptr ? 0 : -1;
    		}
    		if(s2 == nullptr) {
    			return 1;
    		}
    		return std::strcmp(s1, s2);
    	}
    	inline static int stringEqual(const char* s1, const char* s2) {
    		return stringCmp(s1, s2) == 0;
    	}
    };

protected:
	Streams(const char* aTypeName)
	: typeName(aTypeName)
	{ }

private:
	const char* typeName;
};

} /* namespace monitoring */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_MONITORING_STREAMS_H_ */
