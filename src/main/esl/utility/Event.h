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

#ifndef ESL_UTILITY_EVENT_H_
#define ESL_UTILITY_EVENT_H_

#include <esl/object/Object.h>
#include <esl/utility/Enum.h>

#include <string>

namespace esl {
namespace utility {

class Event : public object::Object {
public:
	enum EnumType {
		unknown,
		stop,
		stopping,
		stopped
	};

	using Type = Enum<EnumType, EnumType::unknown>;

	Event(const Type& aType, const object::Object& aSender);

	const Type& getType() const noexcept;
	const object::Object& getSender() const noexcept;

private:
	const Type type;
	const object::Object& sender;
};

template<>
const std::string& Enum<Event::EnumType, Event::EnumType::unknown>::toString(Event::EnumType eventType) noexcept;

} /* namespace utility */
} /* namespace esl */

#endif /* ESL_UTILITY_EVENT_H_ */
