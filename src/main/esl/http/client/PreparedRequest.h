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

#ifndef ESL_HTTP_CLIENT_PREPAREDREQUEST_H_
#define ESL_HTTP_CLIENT_PREPAREDREQUEST_H_

#include <esl/http/client/Request.h>
#include <esl/http/client/Response.h>
#include <esl/http/client/io/Input.h>
#include <esl/io/Output.h>

#include <memory>

namespace esl {
namespace http {
namespace client {

class PreparedRequest final {
public:
	class Binding {
	public:
		Binding() = default;
		virtual ~Binding() = default;

		virtual Response execute(io::Input& input, esl::io::Output& output) const = 0;
	};

	PreparedRequest() = default;
	PreparedRequest(const PreparedRequest&) = delete;
	PreparedRequest(PreparedRequest&&) = default;
	PreparedRequest(std::unique_ptr<Binding> binding);

	~PreparedRequest() = default;

	explicit operator bool() const noexcept;

	PreparedRequest& operator=(const PreparedRequest&) = delete;
	PreparedRequest& operator=(PreparedRequest&& other) = default;

	PreparedRequest& operator<<(esl::io::Output output);
	PreparedRequest& operator>>(io::Input input);

	Response execute();

private:
	std::unique_ptr<Binding> binding;
	io::Input input;
	esl::io::Output output;
};

} /* namespace client */
} /* namespace http */
} /* namespace esl */

#endif /* ESL_HTTP_CLIENT_PREPAREDREQUEST_H_ */
