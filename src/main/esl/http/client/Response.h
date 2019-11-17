/*
MIT License
Copyright (c) 2019 Sven Lukas

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

#ifndef SRC_MAIN_C___RSM_SERVICE_CLIENT_RESPONSE_H_
#define SRC_MAIN_C___RSM_SERVICE_CLIENT_RESPONSE_H_

#include <string>
#include <map>
#include <cstdlib>

namespace esl {
namespace http {
namespace client {

//class Connection;

// Serverantwort bestehend aus: Http-Rueckgabewert, Antwort als Text und Key-Value Paaren mit Einstellungen
class Response {
friend class Connection; // fuer readCallback;
public:
	Response() noexcept;
	virtual ~Response() noexcept;

	std::string getHeader(const std::string& header) const noexcept;


/* TODO: diese Low-Level-Callback Funktionen muessen noch nach curl::Connection */
	// writedata callback function
	static size_t  writeCallback(void *ptr, size_t size, size_t nmemb, void *userdata);

	// header callback function
	static size_t headerCallback(void *ptr, size_t size, size_t nmemb, void *userdata);



protected:
	virtual size_t read(void* data, size_t size) noexcept = 0;

private:
	size_t readHeader(void *data, size_t size) noexcept;

	std::map<std::string, std::string> headers;
};

} /* namespace client */
} /* namespace http */
} /* namespace esl */

#endif /* SRC_MAIN_C___RSM_SERVICE_CLIENT_RESPONSE_H_ */
