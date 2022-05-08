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

#ifndef ESL_OBJECT_INTERFACE_H_
#define ESL_OBJECT_INTERFACE_H_

#include <esl/Module.h>
#include <esl/module/Interface.h>
#include <esl/module/Module.h>

#include <string>
#include <vector>
#include <utility>
#include <memory>

namespace esl {
namespace object {

struct Interface : module::Interface {
	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	class Object {
	public:
		virtual ~Object() = default;
	};

	using CreateObject = std::unique_ptr<Object>(*)(const std::vector<std::pair<std::string, std::string>>&);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */
	static inline const char* getType() {
		return "esl-object";
	}

	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	static std::unique_ptr<const module::Interface> createInterface(const char* implementation, CreateObject createObject) {
		return std::unique_ptr<const module::Interface>(new Interface(implementation, createObject));
	}

	Interface(const char* implementation, CreateObject aCreateObject)
	: module::Interface(getModule().getId(), getType(), implementation, getModule().getApiVersion()),
	  createObject(aCreateObject)
	{ }

	CreateObject createObject;
};

} /* namespace object */
} /* namespace esl */

#endif /* ESL_OBJECT_INTERFACE_H_ */
