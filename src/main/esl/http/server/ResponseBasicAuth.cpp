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

#include <esl/http/server/ResponseBasicAuth.h>

namespace esl {
namespace http {
namespace server {

ResponseBasicAuth::ResponseBasicAuth(std::string aRealmId, const esl::utility::MIME& contentType, const char* contentData, size_t contentDataSize)
: ResponseBasicAuth(std::move(aRealmId), contentType.toString(), contentData, contentDataSize)
{ }

ResponseBasicAuth::ResponseBasicAuth(std::string aRealmId, const std::string& contentType, const char* contentData, size_t contentDataSize)
: ResponseStatic(401, contentType, contentData, contentDataSize),
  realmId(std::move(aRealmId))
{ }

const std::string& ResponseBasicAuth::getRealmId() const noexcept {
	return realmId;
}

} /* namespace server */
} /* namespace http */
} /* namespace esl */
