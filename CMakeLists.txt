cmake_minimum_required(VERSION 3.23)

project(esl VERSION 1.5.0
            DESCRIPTION "Enterprise Support Library"
            LANGUAGES CXX)

#include(FetchContent)
#FetchContent_Declare(
#  catch
#  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#  GIT_TAG        v2.13.6
#)
#FetchContent_MakeAvailable(catch)

# The compiled library code is here
#add_subdirectory(src/main)
# STATIC, SHARED, MODULE, INTERFACE
add_library(esl STATIC
        ./src/main/esl/plugin/Registry.cpp
        ./src/main/esl/plugin/BasePlugin.h
        ./src/main/esl/plugin/exception/PluginNotFound.h
        ./src/main/esl/plugin/exception/PluginNotFound.cpp
        ./src/main/esl/plugin/Registry.h
        ./src/main/esl/plugin/Plugin.h
        ./src/main/esl/plugin/Library.h
        ./src/main/esl/plugin/Library.cpp
        ./src/main/esl/ESL.h
        ./src/main/esl/Version.h
        ./src/main/esl/crypto/PublicKey.h
        ./src/main/esl/crypto/KeyStore.h
        ./src/main/esl/crypto/PrivateKey.h
        ./src/main/esl/system/Stacktrace.cpp
        ./src/main/esl/system/Stacktrace.h
        ./src/main/esl/system/FileDescriptor.h
        ./src/main/esl/system/exception/ProcessError.h
        ./src/main/esl/system/exception/ProcessError.cpp
        ./src/main/esl/system/Arguments.h
        ./src/main/esl/system/Environment.h
        ./src/main/esl/system/Signal.h
        ./src/main/esl/system/FileDescriptor.cpp
        ./src/main/esl/system/Environment.cpp
        ./src/main/esl/system/Process.h
        ./src/main/esl/system/Transceiver.cpp
        ./src/main/esl/system/Transceiver.h
        ./src/main/esl/system/Arguments.cpp
        ./src/main/esl/database/Diagnostics.cpp
        ./src/main/esl/database/Column.h
        ./src/main/esl/database/ConnectionFactory.h
        ./src/main/esl/database/exception/SqlError.cpp
        ./src/main/esl/database/exception/SqlError.h
        ./src/main/esl/database/PreparedBulkStatement.cpp
        ./src/main/esl/database/PreparedStatement.h
        ./src/main/esl/database/PreparedStatement.cpp
        ./src/main/esl/database/Field.cpp
        ./src/main/esl/database/PreparedBulkStatement.h
        ./src/main/esl/database/Connection.h
        ./src/main/esl/database/Field.h
        ./src/main/esl/database/sql/Engine.h
        ./src/main/esl/database/Diagnostic.h
        ./src/main/esl/database/Column.cpp
        ./src/main/esl/database/table/Tables.h
        ./src/main/esl/database/ResultSet.h
        ./src/main/esl/database/Diagnostics.h
        ./src/main/esl/database/ResultSet.cpp
        ./src/main/esl/utility/Enum.h
        ./src/main/esl/utility/URL.cpp
        ./src/main/esl/utility/Protocol.cpp
        ./src/main/esl/utility/String.h
        ./src/main/esl/utility/UniqueRef.h
        ./src/main/esl/utility/URL.h
        ./src/main/esl/utility/HttpMethod.h
        ./src/main/esl/utility/HttpMethod.cpp
        ./src/main/esl/utility/Signal.h
        ./src/main/esl/utility/Protocol.h
        ./src/main/esl/utility/Signal.cpp
        ./src/main/esl/utility/Event.h
        ./src/main/esl/utility/MIME.cpp
        ./src/main/esl/utility/MIME.h
        ./src/main/esl/utility/String.cpp
        ./src/main/esl/utility/Event.cpp
        ./src/main/esl/io/Input.cpp
        ./src/main/esl/io/input/String.h
        ./src/main/esl/io/input/Closed.cpp
        ./src/main/esl/io/input/Closed.h
        ./src/main/esl/io/input/String.cpp
        ./src/main/esl/io/Output.h
        ./src/main/esl/io/Output.cpp
        ./src/main/esl/io/Writer.h
        ./src/main/esl/io/Standard.h
        ./src/main/esl/io/FilePosition.cpp
        ./src/main/esl/io/Consumer.h
        ./src/main/esl/io/Producer.h
        ./src/main/esl/io/FilePosition.h
        ./src/main/esl/io/Standard.cpp
        ./src/main/esl/io/Reader.h
        ./src/main/esl/io/output/Buffered.h
        ./src/main/esl/io/output/Function.cpp
        ./src/main/esl/io/output/String.h
        ./src/main/esl/io/output/Buffered.cpp
        ./src/main/esl/io/output/File.cpp
        ./src/main/esl/io/output/Memory.h
        ./src/main/esl/io/output/File.h
        ./src/main/esl/io/output/String.cpp
        ./src/main/esl/io/output/Function.h
        ./src/main/esl/io/output/Memory.cpp
        ./src/main/esl/io/Input.h
        ./src/main/esl/logging/Location.h
        ./src/main/esl/logging/Logger.cpp
        ./src/main/esl/logging/StreamWriter.h
        ./src/main/esl/logging/StreamReal.h
        ./src/main/esl/logging/StreamWriter.cpp
        ./src/main/esl/logging/Layout.h
        ./src/main/esl/logging/OStream.h
        ./src/main/esl/logging/Logging.cpp
        ./src/main/esl/logging/Appender.h
        ./src/main/esl/logging/StreamReal.cpp
        ./src/main/esl/logging/StreamEmpty.h
        ./src/main/esl/logging/Level.h
        ./src/main/esl/logging/Logging.h
        ./src/main/esl/logging/Streams.h
        ./src/main/esl/logging/Logger.h
        ./src/main/esl/object/Cloneable.h
        ./src/main/esl/object/Control.h
        ./src/main/esl/object/InitializeContext.h
        ./src/main/esl/object/Value.h
        ./src/main/esl/object/MetaData.h
        ./src/main/esl/object/Event.h
        ./src/main/esl/object/Context.h
        ./src/main/esl/object/Implementations.h
        ./src/main/esl/object/Object.h
        ./src/main/esl/object/Bean.h
        ./src/main/esl/Logger.h
        ./src/main/esl/processing/BasicContext.h
        ./src/main/esl/processing/Task.cpp
        ./src/main/esl/processing/TaskFactory.h
        ./src/main/esl/processing/RefProcedure.h
        ./src/main/esl/processing/Context.h
        ./src/main/esl/processing/Status.h
        ./src/main/esl/processing/job/Job.cpp
        ./src/main/esl/processing/job/Job.h
        ./src/main/esl/processing/job/JobFactory.h
        ./src/main/esl/processing/Procedure.h
        ./src/main/esl/processing/Context.cpp
        ./src/main/esl/processing/Task.h
        ./src/main/esl/processing/TaskDescriptor.h
        ./src/main/esl/com/basic/server/RequestHandler.h
        ./src/main/esl/com/basic/server/Connection.h
        ./src/main/esl/com/basic/server/RequestContext.h
        ./src/main/esl/com/basic/server/Request.h
        ./src/main/esl/com/basic/server/Socket.h
        ./src/main/esl/com/basic/client/ConnectionFactory.h
        ./src/main/esl/com/basic/client/Response.h
        ./src/main/esl/com/basic/client/Connection.h
        ./src/main/esl/com/basic/client/Request.h
        ./src/main/esl/com/http/server/Response.cpp
        ./src/main/esl/com/http/server/exception/StatusCode.cpp
        ./src/main/esl/com/http/server/exception/StatusCode.h
        ./src/main/esl/com/http/server/RequestHandler.h
        ./src/main/esl/com/http/server/Response.h
        ./src/main/esl/com/http/server/Connection.h
        ./src/main/esl/com/http/server/RequestContext.h
        ./src/main/esl/com/http/server/Request.h
        ./src/main/esl/com/http/server/Socket.h
        ./src/main/esl/com/http/client/Response.cpp
        ./src/main/esl/com/http/client/ConnectionFactory.h
        ./src/main/esl/com/http/client/exception/NetworkError.cpp
        ./src/main/esl/com/http/client/exception/NetworkError.h
        ./src/main/esl/com/http/client/Response.h
        ./src/main/esl/com/http/client/Request.cpp
        ./src/main/esl/com/http/client/Connection.h
        ./src/main/esl/com/http/client/Request.h
)

target_include_directories(esl PUBLIC ./src/main)
target_compile_features(esl PUBLIC cxx_std_11)
set_property(TARGET esl PROPERTY POSITION_INDEPENDENT_CODE ON)

find_package(Boost REQUIRED)

target_link_libraries(esl PRIVATE Boost::boost)

install(TARGETS esl
        EXPORT esl-export
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

install(EXPORT      esl-export
        FILE        eslTargets.cmake
        NAMESPACE   esl::
        DESTINATION lib/cmake
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/eslConfig.cmake
        DESTINATION "lib/cmake"
)

# The compiled test code is here
#add_subdirectory(src/test)
