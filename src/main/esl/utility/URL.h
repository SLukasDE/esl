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

#ifndef ESL_UTILITY_URL_H_
#define ESL_UTILITY_URL_H_

#include <esl/utility/Protocol.h>

#include <string>

namespace esl {
namespace utility {

class URL {
public:
	URL(const std::string& url);

	const Protocol& getScheme() const;
	const std::string& getHostname() const;
	const std::string& getPort() const;
	const std::string& getPath() const;
	const std::string& getQuery() const;
	const std::string& getTag() const;

private:
	enum class NextFragment {
		SCHEME,
		HOSTNAME,
		PORT,
		PATH,
		QUERY,
		TAG,
		EMPTY
	};
	NextFragment parseScheme(size_t& pos, const char* str, const size_t len);
	NextFragment parseHostname(size_t& pos, const char* str, const size_t len);
	NextFragment parsePort(size_t& pos, const char* str, const size_t len);
	NextFragment parsePath(size_t& pos, const char* str, const size_t len);
	NextFragment parseQuery(size_t& pos, const char* str, const size_t len);
	NextFragment parseTag(size_t& pos, const char* str, const size_t len);

	Protocol scheme;
	std::string hostname;
	std::string port;
	std::string path;
	std::string query;
	std::string tag;
};

} /* namespace utility */
} /* namespace esl */

#endif /* ESL_UTILITY_URL_H_ */
