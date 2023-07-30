/*
MIT License
Copyright (c) 2019-2023 Sven Lukas

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

#ifndef ESL_COM_COMMON_SERVER_REQUESTCONTEXT_H_
#define ESL_COM_COMMON_SERVER_REQUESTCONTEXT_H_

#include <esl/com/basic/server/RequestContext.h>
#include <esl/com/http/server/RequestContext.h>
#include <esl/object/Context.h>
#include <esl/object/Object.h>

namespace esl {
inline namespace v1_6 {
namespace com {
namespace common {
namespace server {

class RequestContext : public object::Object {
public:
	virtual basic::server::RequestContext* getBasicRequestContext() = 0;
	virtual const basic::server::RequestContext* getBasicRequestContext() const = 0;

	virtual http::server::RequestContext* getHttpRequestContext() = 0;
	virtual const http::server::RequestContext* getHttpRequestContext() const = 0;

	virtual object::Context& getObjectContext() = 0;
};

} /* namespace server */
} /* namespace common */
} /* namespace com */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_COM_COMMON_SERVER_REQUESTCONTEXT_H_ */
