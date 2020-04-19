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

#include <esl/utility/MIME.h>
#include <algorithm>

namespace esl {
namespace utility {

MIME::MIME(std::string mediaType, std::string subType) noexcept
: mediaType(mediaType),
  subType(subType)
{ }

std::string MIME::getContentType() noexcept {
	return mediaType + "/" + subType;
}

MIME MIME::byFilename(const std::string& filename) {
    std::size_t pos = filename.find_last_of(".");
    std::string fileType;

    /* Dateiendung gefunden */
    if(pos != std::string::npos) {
        fileType = filename.substr(pos+1);
        std::transform(fileType.begin(), fileType.end(), fileType.begin(), tolower);
    }


    if(fileType == "bmp") {
        return MIME("image", "bmp");
    }
    else if(fileType == "bz") {
        return MIME("application", "x-bzip");
    }
    else if(fileType == "bz2") {
        return MIME("application", "x-bzip2");
    }
    else if(fileType == "gif") {
        return MIME("image", "gif");
    }
    else if(fileType == "gz") {
        return MIME("application", "x-compressed");
    }
    else if(fileType == "gzip") {
        return MIME("application", "x-gzip");
    }
    else if(fileType == "htm") {
        return MIME("text", "html");
    }
    else if(fileType == "html") {
        return MIME("text", "html");
    }
    else if(fileType == "jpg" || fileType == "jpeg") {
        return MIME("image", "jpeg");
    }
    else if(fileType == "log") {
        return MIME("text", "plain");
    }
    else if(fileType == "mp3") {
        return MIME("audio", "mpeg3");
    }
    else if(fileType == "png") {
        return MIME("image", "png");
    }
    else if(fileType == "text") {
        return MIME("text", "plain");
    }
    else if(fileType == "txt") {
        return MIME("text", "plain");
    }
    else if(fileType == "tgz") {
        return MIME("application", "x-compressed");
    }
    else if(fileType == "tif") {
        return MIME("image", "tiff");
    }
    else if(fileType == "wav") {
        return MIME("audio", "wav");
    }
    else if(fileType == "xls") {
        return MIME("application", "excel");
    }
    else if(fileType == "xml") {
        return MIME("text", "xml");
    }
    else if(fileType == "zip") {
        return MIME("application", "zip");
    }
    MIME m;
    return m;
}

} /* namespace utility */
} /* namespace esl */

