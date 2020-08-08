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

#ifndef ESL_HTTP_CLIENT_REQUESTHANDLERDYNAMIC_H_
#define ESL_HTTP_CLIENT_REQUESTHANDLERDYNAMIC_H_

#include <esl/http/client/RequestHandler.h>
#include <esl/utility/MIME.h>

#include <functional>
#include <string>

namespace esl {
namespace http {
namespace client {

class RequestHandlerDynamic: public RequestHandler {
public:
	RequestHandlerDynamic(utility::MIME contentType, std::function<std::size_t(char*, std::size_t)> getDataFunction);
	RequestHandlerDynamic(utility::MIME contentType, std::string data);

	std::size_t producer(char* buffer, std::size_t count) override;

	/* return true if size is available already. if not, getSize() still works, but might be a very expensive call */
	bool hasSize() const override;

	/* this can be a very expensive call if getDataFunction has been specified */
	std::size_t getSize() const override;

	/* instead of calling getSize() to check if it return 0, it's much cheaper to call isEmpty().
	 * Calling isEmpty() will prefetch at most 1024 bytes.
	 */
	bool isEmpty() const override;

private:
	enum DynamicType {
		dataFunction,
		dataString
	};

	std::size_t prefetchData(std::size_t count) const;

	DynamicType dynamicType;

	mutable std::function<std::size_t(char*, std::size_t)> getDataFunction;
	mutable std::size_t fetchedDirectSize = 0;

	mutable std::string data;
	std::size_t dataPos = 0;
};

} /* namespace client */
} /* namespace http */
} /* namespace esl */

#endif /* ESL_HTTP_CLIENT_REQUESTHANDLERDYNAMIC_H_ */
