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

#ifndef SRC_MAIN_C___ESL_HTTP_CLIENT_RESPONSEOBJECT_H_
#define SRC_MAIN_C___ESL_HTTP_CLIENT_RESPONSEOBJECT_H_

#include <esl/http/client/Response.h>
#include <esl/Stacktrace.h>
#include <string>
#include <cstdlib>
#if 0
#include <sergut/XmlDeserializerTiny.h>

namespace esl {
namespace http {
namespace client {


class Connection;

template<typename DT>
class ResponseObject: public Response {
public:
	ResponseObject(const std::string& aOuterTagName, const sergut::ValueType aValueType)
	: outerTagName(aOuterTagName)
	, valueType(aValueType)
	{ }

	ResponseObject(const std::string& aOuterTagName, const std::string& aInnerTagName)
	: outerTagName(aOuterTagName)
	, innerTagName(aInnerTagName)
	{ }

	virtual ~ResponseObject() noexcept { }


	DT getObject() const {
		std::string contentType;
		contentType = getHeader("Content-Type");
		if(!contentType.empty() && contentType != "application/xml") {
	        esl::Stacktrace::rethrow(std::runtime_error("unsupported content type: '" + contentType + "'"));
		}
		if(innerTagName.empty()) {
			sergut::XmlDeserializerTiny deser(data);
			return deser.deserializeData<DT>(outerTagName.c_str(), valueType);
		}

		sergut::XmlDeserializerTiny deser(data);
		return deser.deserializeNestedData<DT>(outerTagName.c_str(), innerTagName.c_str());
	}

protected:
	size_t read(void* aData, size_t size) noexcept override {
		data.append(reinterpret_cast<char*>(aData), size);

		return size;
	}

private:
	std::string outerTagName;
	sergut::ValueType valueType = sergut::ValueType::Attribute;
	std::string innerTagName;
	std::string data;
};

} /* namespace client */
} /* namespace http */
} /* namespace esl */
#endif

#endif /* SRC_MAIN_C___ESL_HTTP_CLIENT_RESPONSEOBJECT_H_ */
