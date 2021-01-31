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

#include <esl/http/server/ResponseStatic.h>

namespace esl {
namespace http {
namespace server {

ResponseStatic::ResponseStatic(unsigned short httpStatus, const esl::utility::MIME& contentType, const char* aContentData, size_t aContentDataSize)
: ResponseStatic(httpStatus, contentType.toString(), aContentData, aContentDataSize)
{ }

ResponseStatic::ResponseStatic(unsigned short httpStatus, const std::string& contentType, const char* aContentData, size_t aContentDataSize)
: Response(httpStatus, contentType),
  contentData(aContentData),
  contentDataSize(aContentDataSize)
{ }

const char* ResponseStatic::getContentData() const noexcept {
	return contentData;
}

std::size_t ResponseStatic::getContentDataSize() const noexcept {
	return contentDataSize;
}

} /* namespace server */
} /* namespace http */
} /* namespace esl */
