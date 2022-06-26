#if 0
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

#ifndef ESL_MODULE_INTERFACETYPE_H_
#define ESL_MODULE_INTERFACETYPE_H_

#include <string>

namespace esl {
namespace module {

class InterfaceType {
public:
	enum Type {
		esl__com__basic__client,
		esl__com__basic__server,
		esl__com__basic__server__requesthandler,
		esl__com__http__client,
		esl__com__http__server,
		esl__com__http__server__requesthandler,
		esl__database,
		esl__object
	};

	InterfaceType() = default;
	InterfaceType(Type type) noexcept;
	explicit InterfaceType(std::string type) noexcept;

	explicit operator bool() const noexcept;

	bool operator==(Type type) const noexcept;
	bool operator==(const InterfaceType& interfaceType) const noexcept;

	bool operator!=(Type type) const noexcept;
	bool operator!=(const InterfaceType& interfaceType) const noexcept;

	const std::string& toString() const noexcept;
	static const std::string& toString(Type type) noexcept;

private:
	bool hasEnum = false;
	Type enumType = esl__object;
	std::string stringType;
};

} /* namespace module */
} /* namespace esl */

#endif /* ESL_MODULE_INTERFACETYPE_H_ */
#endif
