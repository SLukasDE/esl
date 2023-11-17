/*
 * This file is part of ESL.
 * Copyright (C) 2020-2023 Sven Lukas
 *
 * ESL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ESL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser Public License
 * along with ESL.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef ESL_ESL_H_
#define ESL_ESL_H_

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

#include <esl/monitoring/Appender.h>
#include <esl/monitoring/Layout.h>
#include <esl/monitoring/Logging.h>
#include <esl/monitoring/Logger.h>
#include <esl/monitoring/OStream.h>
#include <esl/monitoring/Streams.h>

#include <esl/object/Bean.h>
#include <esl/object/Cloneable.h>
#include <esl/object/Context.h>
#include <esl/object/Control.h>
#include <esl/object/Event.h>
#include <esl/object/Implementations.h>
#include <esl/object/InitializeContext.h>
#include <esl/object/MetaData.h>
#include <esl/object/Object.h>
#include <esl/object/Procedure.h>
#include <esl/object/ProcessingContext.h>
#include <esl/object/Value.h>

#include <esl/plugin/Library.h>
#include <esl/plugin/Plugin.h>
#include <esl/plugin/Registry.h>

#include <esl/system/exception/ProcessError.h>
#include <esl/system/Arguments.h>
#include <esl/system/Environment.h>
#include <esl/system/FileDescriptor.h>
#include <esl/system/Process.h>
#include <esl/system/Task.h>
#include <esl/system/TaskFactory.h>
#include <esl/system/Transceiver.h>
#include <esl/system/Signal.h>
#include <esl/system/Stacktrace.h>

#include <esl/utility/Enum.h>
#include <esl/utility/Event.h>
#include <esl/utility/HttpMethod.h>
#include <esl/utility/MIME.h>
#include <esl/utility/Protocol.h>
#include <esl/utility/RefProcedure.h>
#include <esl/utility/Signal.h>
#include <esl/utility/String.h>
#include <esl/utility/UniqueRef.h>
#include <esl/utility/URL.h>

namespace esl {
inline namespace v1_6 {

template <class E>
inline system::Stacktrace::Injector<E> addStacktrace(const E& e) {
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

} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_ESL_H_ */
