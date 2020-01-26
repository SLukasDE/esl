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

#include <esl/http/client/Response.h>
#include <algorithm>

namespace esl {
namespace http {
namespace client {

namespace {
std::string &ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
std::string &rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
}
}


Response::Response() noexcept
{
}

Response::~Response() noexcept
{
}

::std::string Response::getHeader(const std::string& header) const noexcept
{
	::std::string ret;
	const auto headerIt = headers.find(header);
	if(headerIt != headers.end()) {
		ret = headerIt->second;
	}
	return ret;
}



size_t Response::readHeader(void *data, size_t size) noexcept {
	std::string header(reinterpret_cast<char*>(data), size);
	size_t seperator = header.find_first_of(":");

	if(seperator == std::string::npos) {
		//roll with non seperated headers...
		trim(header);
		if(header.size() == 0) {
			return size; //blank line;
		}
		headers[header] = "";
	}
	else {
		std::string key = header.substr(0, seperator);
		trim(key);
		std::string value = header.substr(seperator + 1);
		trim (value);
		headers[key] = value;
	}

	return size;
}

/**
* @brief write callback function for libcurl
*
* @param data returned data of size (size*nmemb)
* @param size size parameter
* @param nmemb memblock parameter
* @param userdata pointer to user data to save/work with return data
*
* @return (size * nmemb)
*/
size_t Response::writeCallback(void *data, size_t size, size_t nmemb, void *userdata)
{
	Response* r = static_cast<Response*>(userdata);
	return r->read(data, size*nmemb);
}

/**
* @brief header callback for libcurl
*
* @param data returned (header line)
* @param size of data
* @param nmemb memblock
* @param userdata pointer to user data object to save headr data
* @return size * nmemb;
*/
size_t Response::headerCallback(void *data, size_t size, size_t nmemb, void *userdata) {
	Response* r = static_cast<Response*>(userdata);
	return r->readHeader(data, size*nmemb);
}

} /* namespace client */
} /* namespace http */
} /* namespace esl */


