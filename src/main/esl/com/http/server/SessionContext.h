/*
MIT License
Copyright (c) 2019-2021 Sven Lukas

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
#if 0
#ifndef ESL_COM_HTTP_SERVER_SESSIONCONTEXT_H_
#define ESL_COM_HTTP_SERVER_SESSIONCONTEXT_H_

#include <esl/object/Interface.h>
#include <esl/object/Settings.h>
#include <esl/com/http/server/RequestContext.h>

namespace esl {
namespace com {
namespace http {
namespace server {

class SessionContext : public esl::object::Settings {
public:
	virtual esl::object::Interface::Object& getSession(RequestContext& requestContext) const = 0;
};

} /* namespace server */
} /* namespace http */
} /* namespace com */
} /* namespace esl */

#endif /* ESL_COM_HTTP_SERVER_SESSIONCONTEXT_H_ */
#endif
