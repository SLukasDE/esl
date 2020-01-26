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

#ifndef SRC_MAIN_C___ESL_HTTP_CLIENT_REQUESTOBJECT_H_
#define SRC_MAIN_C___ESL_HTTP_CLIENT_REQUESTOBJECT_H_

#include <esl/http/client/RequestStatic.h>
#include <esl/Stacktrace.h>
#include <string>
#if 0
#include <sergut/XmlSerializer.h>

namespace esl {
namespace http {
namespace client {

template<typename DT>
class RequestObject : public RequestStatic {
public:
	RequestObject(const std::string& servicePath, const std::string& contentType,
	              const std::string& outerTagName, const DT& data);

	RequestObject(const std::string& servicePath, const std::string& contentType,
	              const std::string& outerTagName, const std::string& innerTagName,
	              const DT& data);

private:
	static ::std::string serialize(const std::string& contentType,
	                               const std::string& outerTagName,
	                               const DT& data);

	static ::std::string serialize(const std::string& contentType,
	                               const std::string& outerTagName,
	                               const std::string& innerTagName,
	                               const DT& data);
};

template<typename DT>
RequestObject<DT>::RequestObject(const std::string& servicePath,
                                 const std::string& contentType,
                                 const std::string& outerTagName,
                                 const DT& data)
	: RequestStatic(servicePath, contentType, serialize(contentType, outerTagName, data))
{ }

template<typename DT>
RequestObject<DT>::RequestObject(const std::string& servicePath,
                                 const std::string& contentType,
                                 const std::string& outerTagName,
                                 const std::string& innerTagName,
                                 const DT& data)
	: RequestStatic(servicePath, contentType, serialize(contentType, outerTagName, innerTagName, data))
{ }

template<typename DT>
std::string RequestObject<DT>::serialize(const std::string& contentType,
                                           const std::string& outerTagName,
                                           const DT& data)
{
	if(contentType != "application/xml") {
        esl::Stacktrace::rethrow(std::runtime_error("unsupported output format"));
	}
	sergut::XmlSerializer ser;
	RSM_TRY_CATCH(ser.serializeData(outerTagName.c_str(), data));
	return ser.str();
}

template<typename DT>
std::string RequestObject<DT>::serialize(const std::string& contentType,
                                           const std::string& outerTagName,
                                           const std::string& innerTagName,
                                           const DT& data)
{
	if(contentType != "application/xml") {
        esl::Stacktrace::rethrow(std::runtime_error("unsupported output format"));
	}
	sergut::XmlSerializer ser;
	RSM_TRY_CATCH(ser.serializeNestedData(outerTagName.c_str(), innerTagName.c_str(), data));
	return ser.str();
}

} /* namespace client */
} /* namespace http */
} /* namespace esl */
#endif

#endif /* SRC_MAIN_C___ESL_HTTP_CLIENT_REQUESTOBJECT_H_ */
