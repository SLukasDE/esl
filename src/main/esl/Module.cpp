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

#include <esl/Module.h>
#include <esl/module/Interface.h>
#include <esl/logging/layout/Interface.h>
#include <esl/Stacktrace.h>
#include <stdexcept>
#include <new>         // placement new
#include <type_traits> // aligned_storage

namespace esl {

namespace {

class Module : public module::Module {
public:
	Module();
};

typename std::aligned_storage<sizeof(esl::module::Module), alignof(esl::module::Module)>::type moduleBuffer; // memory for the object;
esl::module::Module* modulePtr = nullptr;

Module::Module()
: module::Module()
{
	module::Module::initialize(*this);
}

}  /* anonymous namespace */

module::Module& getModule() {
	if(modulePtr == nullptr) {
		/* ***************** *
		 * initialize module *
		 * ***************** */

		modulePtr = reinterpret_cast<Module*> (&moduleBuffer);
		new (modulePtr) Module; // placement new
	}

	return *modulePtr;
}

void setModule(module::Module& module) {
	modulePtr = &module;
}

} /* namespace esl */
