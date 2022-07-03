/*
MIT License
Copyright (c) 2019-2022 Sven Lukas

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

#ifndef ESL_ESL_H_
#define ESL_ESL_H_

//#include <esl/boot/context/BasicContext.h>
#include <esl/boot/context/Context.h>
#include <esl/boot/logging/Config.h>

#include <esl/com/basic/client/Connection.h>
#include <esl/com/basic/client/ConnectionFactory.h>
#include <esl/com/basic/client/Request.h>
#include <esl/com/basic/client/Response.h>
#include <esl/com/basic/server/Connection.h>
#include <esl/com/basic/server/RequestHandler.h>
#include <esl/com/basic/server/Socket.h>
#include <esl/com/basic/server/Request.h>
#include <esl/com/basic/server/RequestContext.h>

#include <esl/com/http/client/exception/NetworkError.h>
#include <esl/com/http/client/Connection.h>
#include <esl/com/http/client/ConnectionFactory.h>
#include <esl/com/http/client/Request.h>
#include <esl/com/http/client/Response.h>
#include <esl/com/http/server/exception/StatusCode.h>
#include <esl/com/http/server/Connection.h>
#include <esl/com/http/server/RequestHandler.h>
#include <esl/com/http/server/Socket.h>
#include <esl/com/http/server/Request.h>
#include <esl/com/http/server/RequestContext.h>
#include <esl/com/http/server/Response.h>

#include <esl/database/Column.h>
#include <esl/database/Connection.h>
#include <esl/database/Diagnostics.h>
#include <esl/database/Field.h>
#include <esl/database/ConnectionFactory.h>
#include <esl/database/PreparedBulkStatement.h>
#include <esl/database/PreparedStatement.h>
#include <esl/database/ResultSet.h>

#include <esl/io/input/Closed.h>
#include <esl/io/input/String.h>
#include <esl/io/output/Buffered.h>
#include <esl/io/output/File.h>
#include <esl/io/output/Function.h>
#include <esl/io/output/Memory.h>
#include <esl/io/output/String.h>
#include <esl/io/Consumer.h>
#include <esl/io/Input.h>
#include <esl/io/Output.h>
#include <esl/io/Producer.h>
#include <esl/io/Reader.h>
#include <esl/io/Standard.h>
#include <esl/io/Writer.h>

#include <esl/logging/Config.h>
#include <esl/logging/Appender.h>
#include <esl/logging/Layout.h>
#include <esl/logging/Logging.h>
#include <esl/logging/Level.h>
#include <esl/logging/Location.h>
#include <esl/logging/Logger.h>
#include <esl/logging/OStream.h>
#include <esl/logging/StreamEmpty.h>
#include <esl/logging/StreamReal.h>
#include <esl/logging/Streams.h>
#include <esl/logging/StreamWriter.h>

#include <esl/object/Bean.h>
#include <esl/object/Cloneable.h>
#include <esl/object/Context.h>
#include <esl/object/Control.h>
#include <esl/object/Event.h>
#include <esl/object/Implementations.h>
#include <esl/object/InitializeContext.h>
#include <esl/object/MetaData.h>
#include <esl/object/Object.h>
#include <esl/object/Value.h>

#include <esl/plugin/Library.h>
#include <esl/plugin/Plugin.h>
#include <esl/plugin/Registry.h>

#include <esl/processing/Procedure.h>
#include <esl/processing/RefProcedure.h>
#include <esl/processing/TaskDescriptor.h>
#include <esl/processing/TaskFactory.h>
#include <esl/processing/Status.h>
#include <esl/processing/Task.h>

#include <esl/system/exception/ProcessError.h>
#include <esl/system/Arguments.h>
#include <esl/system/Environment.h>
#include <esl/system/FileDescriptor.h>
#include <esl/system/Process.h>
#include <esl/system/Transceiver.h>
#include <esl/system/Signal.h>
#include <esl/system/Stacktrace.h>

#include <esl/utility/Enum.h>
#include <esl/utility/Event.h>
#include <esl/utility/HttpMethod.h>
#include <esl/utility/MIME.h>
#include <esl/utility/Protocol.h>
#include <esl/utility/Signal.h>
#include <esl/utility/String.h>
#include <esl/utility/UniqueRef.h>
#include <esl/utility/URL.h>

namespace esl {

template <class E>
inline system::StacktraceInjector<E> addStacktrace(const E& e) {
	return system::Stacktrace::add(e);
}

template <class E>
const system::Stacktrace* getStacktrace(const E& e) {
	return system::Stacktrace::get(e);
}

template<typename F, typename... Args>
auto callStacktrace(F f, Args... args) -> decltype(f(args...)) {
	try {
		return f(args...);
    }
	catch (std::exception& e) {
		if(system::Stacktrace::get(e)) {
			throw;
		}
		throw system::Stacktrace::add(e);
    }
    catch (...) {
        throw;
    }
}

} /* namespace esl */

#endif /* ESL_ESL_H_ */
