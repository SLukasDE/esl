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

#include <esl/Module.h>
#include <esl/bootstrap/Interface.h>
#include <new>         // placement new
#include <type_traits> // aligned_storage

namespace esl {

namespace {
class Module : public esl::bootstrap::Module {
public:
	Module() = default;
	~Module() = default;

	void addModule(const esl::bootstrap::Module& foreignModule);
};

typename std::aligned_storage<sizeof(Module), alignof(Module)>::type moduleBuffer; // memory for the object;
Module& module = reinterpret_cast<Module&> (moduleBuffer);

void Module::addModule(const esl::bootstrap::Module& foreignModule) {
	esl::bootstrap::Interface* interfacePtr = nullptr;

	/* ***************************************************** *
	 * Calling "install" of each interface of the new module *
	 * This might be necessary, if an Module needs some API  *
	 * by itself.                                            *
	 * ***************************************************** */
#if 0
	interfacePtr = const_cast<esl::bootstrap::Interface*>(&foreignModule.getInterfacesProvided());
	while(interfacePtr->next != nullptr) {
		if(interfacePtr->install != nullptr) {
			interfacePtr->install(interfacesProvided);
		}
		interfacePtr = interfacePtr->next;
	}
#endif
	/* ***************************************************** *
	 * Now install new interfaces to own module              *
	 * ***************************************************** */
	/* go to last interface */
	interfacePtr = &interfacesProvided;
	while(interfacePtr->next != nullptr) {
		interfacePtr = interfacePtr->next;
	}

	/* install new interfaces */
	interfacePtr->next = const_cast<esl::bootstrap::Interface*>(&foreignModule.getInterfacesProvided());
}

void initialize() {
	static bool isInitialized = false;

	if(isInitialized == false) {
		isInitialized = true;
		new (&module) Module(); // placement new
		esl::bootstrap::Module::initialize(module);
	}
}
}

const esl::bootstrap::Module& getModule() {
	initialize();
	return module;
}

void addModule(const esl::bootstrap::Module& aModule) {
	initialize();
	module.addModule(aModule);
}

} /* namespace esl */
