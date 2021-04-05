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

#ifndef ESL_HTTP_CLIENT_CONNECTION_H_
#define ESL_HTTP_CLIENT_CONNECTION_H_

#include <esl/http/client/Interface.h>
#include <esl/http/client/Request.h>
#include <esl/http/client/PreparedRequest.h>
#include <esl/utility/URL.h>
#include <esl/object/Values.h>
#include <esl/module/Implementation.h>

#include <string>
#include <initializer_list>

namespace esl {
namespace http {
namespace client {

class Connection : public Interface::Connection {
public:
	static module::Implementation& getDefault();

	Connection(const utility::URL& hostUrl,
			std::initializer_list<std::pair<std::string, std::string>> settings,
			const std::string& implementation = getDefault().getImplementation());

	Connection(const utility::URL& hostUrl,
			const object::Values<std::string>& settings = getDefault().getSettings(),
			const std::string& implementation = getDefault().getImplementation());

	PreparedRequest prepare(Request&& request) const override;
	PreparedRequest prepare(const Request& request) const override;
/*
	Response send(Request request) const;

    template<typename... Args>
    Response send(Request&& request, Args... args) const {
	    Data data;
	    addArguments(data, std::forward<Args...>(args...));
	    return send(std::move(request), data);
    }

protected:
	Response send(Request&& request, Data& data) const override;
*/
private:
/*
	static void addArguments(Data& data, Input&& input);
	static void addArguments(Data& data, utility::io::Output&& output);

	template<typename... Args>
	static inline void addArguments(Data& data, Input&& input, Args... args) {
		addArguments(data, std::move(input));
    	addArguments(data, std::forward<Args...>(args...));
	}

	template<typename... Args>
	static inline void addArguments(Data& data, utility::io::Output&& output, Args... args) {
		addArguments(data, std::move(output));
    	addArguments(data, std::forward<Args...>(args...));
	}
*/
	std::unique_ptr<Interface::Connection> connection;
};

} /* namespace client */
} /* namespace http */
} /* namespace esl */

#endif /* ESL_HTTP_CLIENT_CONNECTION_H_ */
