/*
MIT License
Copyright (c) 2019-2022 Sven Lukas

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

#include <esl/logging/appender/Appender.h>
#include <esl/Module.h>

namespace esl {
namespace logging {
namespace appender {

module::Implementation& Appender::getDefault() {
	static module::Implementation implementation;
	return implementation;
}

Appender::Appender(const module::Interface::Settings& settings, const std::string& implementation)
: appender(esl::getModule().getInterface<Interface>(implementation).createAppender(settings))
{ }

void Appender::setLayout(const layout::Interface::Layout* layout) {
	appender->setLayout(layout);
}

const layout::Interface::Layout* Appender::getLayout() const {
	return appender->getLayout();
}

/* both methods are NOT thread-safe */
void Appender::setRecordLevel(RecordLevel recordLevel) {
	appender->setRecordLevel(recordLevel);
}

Interface::Appender::RecordLevel Appender::getRecordLevel() const {
	return appender->getRecordLevel();
}

void Appender::flush() {
	return appender->flush();
}

void Appender::flush(std::ostream& oStream) {
	return appender->flush(oStream);
}

void Appender::write(const Location& location, const char* str, std::size_t len) {
	appender->write(location, str, len);
}

} /* namespace appender */
} /* namespace logging */
} /* namespace esl */
