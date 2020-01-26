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


#include <esl/http/server/Connection.h>
#include <esl/Object.h>
#include <esl/http/server/Request.h>
#include <string>

#ifndef ESL_HTTP_SERVER_REQUESTCONTEXT_H_
#define ESL_HTTP_SERVER_REQUESTCONTEXT_H_

namespace esl {
namespace http {
namespace server {

class RequestContext {
public:
//	RequestContext() = default;
	virtual ~RequestContext() = default;

	virtual Connection& getConnection() const = 0;
	virtual const Request& getRequest() const = 0;
	virtual const std::string& getPath() const = 0;

	virtual Object* getObject(const std::string& id) const = 0;
};

} /* namespace server */
} /* namespace http */
} /* namespace esl */

#endif /* ESL_HTTP_SERVER_REQUESTCONTEXT_H_ */
