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

#include <esl/http/server/ResponseDynamic.h>
#include <cstring>

namespace esl {
namespace http {
namespace server {

ResponseDynamic::ResponseDynamic(unsigned short httpStatus, const esl::utility::MIME& contentType, std::function<int(char*, std::size_t)> aGetDataFunction)
: Response(httpStatus, contentType),
  getDataFunction(aGetDataFunction)
{ }

ResponseDynamic::ResponseDynamic(unsigned short httpStatus, const esl::utility::MIME& contentType, std::string aData)
: Response(httpStatus, contentType),
  data(std::move(aData))
{ }
/*
ResponseDynamic::ResponseDynamic(unsigned short httpStatus, const std::string& contentType, std::function<int(char*, std::size_t)> aGetDataFunction)
: Response(httpStatus, contentType),
  getDataFunction(aGetDataFunction)
{ }

ResponseDynamic::ResponseDynamic(unsigned short httpStatus, const std::string& contentType, std::string aData)
: Response(httpStatus, contentType),
  data(std::move(aData))
{ }
*/
int ResponseDynamic::getData(char* buffer, std::size_t count) {
	if(getDataFunction) {
		return getDataFunction(buffer, count);
	}

    std::size_t remainingSize = data.size() - dataPos;

    if(count > remainingSize) {
    	count = remainingSize;
    }
    std::memcpy(buffer, &data.data()[dataPos], count);
    dataPos += count;


    /* Hier wissen wir, dass keine Daten mehr zu senden sind, wenn count == 0 ist */
    /* Daher geben wir dann auch -1 zurueck - was dem Aufrufer signalisiert, dass keine Daten mehr zu senden sind */
    if(count == 0) {
        return -1;
    }
    return count;
}

} /* namespace server */
} /* namespace http */
} /* namespace esl */
