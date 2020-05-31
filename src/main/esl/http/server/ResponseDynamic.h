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

#ifndef ESL_HTTP_SERVER_RESPONSEDYNAMIC_H_
#define ESL_HTTP_SERVER_RESPONSEDYNAMIC_H_

#include <esl/http/server/Response.h>
#include <esl/utility/MIME.h>

#include <functional>

namespace esl {
namespace http {
namespace server {

class ResponseDynamic : public Response {
public:
	ResponseDynamic(unsigned short httpStatus, const esl::utility::MIME& contentType, std::function<int(char*, std::size_t)> getDataFunction);
	ResponseDynamic(unsigned short httpStatus, const esl::utility::MIME& contentType, std::string data);

	ResponseDynamic(unsigned short httpStatus, const std::string& contentType, std::function<int(char*, std::size_t)> getDataFunction);
	ResponseDynamic(unsigned short httpStatus, const std::string& contentType, std::string data);

	int getData(char* buffer, std::size_t count);

private:
	std::function<int(char*, std::size_t)> getDataFunction;
	std::string data;
	std::size_t dataPos = 0;
};

} /* namespace server */
} /* namespace http */
} /* namespace esl */

#endif /* ESL_HTTP_SERVER_RESPONSEDYNAMIC_H_ */
