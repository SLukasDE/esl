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

#include <esl/utility/Event.h>

namespace esl {
namespace utility {

Event::Event(const Type& aType, const object::IObject& aSender)
: type(aType),
  sender(aSender)
{ }

const Event::Type& Event::getType() const noexcept {
	return type;
}

const object::IObject& Event::getSender() const noexcept {
	return sender;
}

template<>
const std::string& Event::Type::toString(Event::EnumType eventType) noexcept {
	static const std::string strEmpty;
	static const std::string strUnknown = "unknown";
	static const std::string strStop = "stop";
	static const std::string strStopping = "stopping";
	static const std::string strStopped = "stopped";

	switch(eventType) {
	case Event::unknown:
		return strUnknown;
	case Event::stop:
		return strStop;
	case Event::stopping:
		return strStopping;
	case Event::stopped:
		return strStopped;
	}

	return strEmpty;
}

} /* namespace utility */
} /* namespace esl */
