/*
MIT License
Copyright (c) 2019-2025 Sven Lukas

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

#include <esl/monitoring/Logging.h>
#include <esl/monitoring/Streams.h>
#include <esl/plugin/Registry.h>

namespace esl {
inline namespace v1_6 {
namespace monitoring {

Streams::Writer::Writer(std::unique_ptr<OStream> aOStream)
: oStream(std::move(aOStream))
{ }

Streams::Writer::Writer(Streams::Writer&& streamWriter)
: oStream(std::move(streamWriter.oStream))
{ }

Streams::Writer& Streams::Writer::operator<<(std::ostream& (*pf)(std::ostream&)) {
	if(oStream) {
		if(oStream->getOStream()) {
			*oStream->getOStream() << pf;
		}

		std::ostream&(*pfFlush)(std::ostream&) = std::flush;
		if(pf == pfFlush) {
			oStream->flush();
		}
	}

	return *this;
}


Streams::Real::Real(const char* aTypeName, Level aLevel)
: typeName(aTypeName),
  level(aLevel)
{ }

Streams::Writer Streams::Real::operator()(const void* object) {
    return Writer(getWriter(object, nullptr, nullptr, 0));
}

Streams::Writer Streams::Real::operator()(const char* function, const char* file, unsigned int lineNo) {
    return Writer(getWriter(nullptr, function, file, lineNo));
}

Streams::Writer Streams::Real::operator()(const void* object, const char* function, const char* file, unsigned int lineNo) {
    return Writer(getWriter(object, function, file, lineNo));
}

Streams::Writer Streams::Real::operator<<(std::ostream& (*pf)(std::ostream&)) {
    Writer writer(getWriter(nullptr, nullptr, nullptr, 0));
    writer << pf;
    return writer;
}

Streams::Real::operator bool() const {
	return logging ? logging->isEnabled(typeName, level) : plugin::Registry::get().findObject<Logging>() ? plugin::Registry::get().findObject<Logging>()->isEnabled(typeName, level) : false;
	//return isEnabled();
}

Streams::Writer Streams::Real::getWriter(const void* object, const char* function, const char* file, unsigned int lineNo) {
	if(!logging) {
		logging = plugin::Registry::get().findObject<Logging>();
	}
	if(!logging) {
		return Writer(nullptr);
	}

	return Writer(logging->createOStream(Location(level, object, typeName, function, file, lineNo, std::this_thread::get_id())));
}

} /* namespace monitoring */
} /* inline namespace v1_6 */
} /* namespace esl */
