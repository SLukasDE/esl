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

#include <esl/logging/StreamWriter.h>
//#include <esl/logging/Logger.h>

#include <esl/logging/Interface.h>
#include <esl/bootstrap/Interface.h>
#include <esl/Module.h>
#include <esl/Stacktrace.h>

//#include <mutex>

namespace esl {
namespace logging {

namespace {

void removeWriter(std::ostream& ostream, void* data) {
	esl::getModule().getInterface(Interface::getId(), Interface::getApiVersion());
	const Interface* interface = static_cast<const Interface*>(esl::getModule().getInterface(Interface::getId(), Interface::getApiVersion()));

	if(interface == nullptr) {
		throw esl::addStacktrace(std::runtime_error("no implementation available for \"esl-logging\""));
	}

	interface->removeWriter(ostream, data);
}

}

StreamWriter::StreamWriter(Id aId, std::ostream& aOStream, void* aData)
//StreamWriter::StreamWriter(std::pair<Id*, std::ostream*> idAndOStream)
: doUnlock(true),
//  id(idAndOStream.first),
  id(std::move(aId)),
//  oStream(*idAndOStream.second)
  oStream(aOStream),
  data(aData)
{
}

StreamWriter::StreamWriter(StreamWriter&& streamWriter)
: doUnlock(streamWriter.doUnlock),
  id(std::move(streamWriter.id)),
  oStream(streamWriter.oStream),
  data(streamWriter.data)
{
	streamWriter.doUnlock = false;
}

StreamWriter::~StreamWriter() {
    if(doUnlock) {
    	oStream.flush();

		removeWriter(oStream, data);
    }
}

StreamWriter& StreamWriter::operator<<(std::ostream& (*pf)(std::ostream&)) {
	oStream << pf;
    return *this;
}

} /* namespace logging */
} /* namespace esl */
