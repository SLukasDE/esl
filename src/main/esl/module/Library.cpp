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

#include <esl/module/Library.h>
#include <esl/Module.h>
#include <stdexcept>

#ifdef linux
#include <dlfcn.h>
#endif

namespace esl {
namespace module {

Library::Library(const std::string& path)
: libGetModule(nullptr)
{
#ifdef linux
	libHandle = dlopen(path.c_str(), RTLD_NOW | RTLD_LOCAL );
    if(libHandle == nullptr) {
    	throw std::runtime_error(dlerror());
    }

    void* symbolAddressEslGetModule = dlsym(libHandle, "esl__module__library__getModule");
    if(symbolAddressEslGetModule == nullptr) {
        if(dlclose(libHandle) != 0) {
        }
        libHandle = nullptr;
    	throw std::runtime_error("Cannot find symbol \"esl__module__library__getModule\" in library \"" + path + "\"");
    }

    if(symbolAddressEslGetModule != nullptr) {
        libGetModule = *static_cast<GetModule*>(symbolAddressEslGetModule);
    }
    if(libGetModule == nullptr) {
        if(dlclose(libHandle) != 0) {
        }
        libHandle = nullptr;
    	throw std::runtime_error("Symbol \"esl__module__library__getModule\" in library \"" + path + "\" is null");
    }
#else
   	throw std::runtime_error("Library loader not implemented so far");
#endif
}

Library::~Library() {
#ifdef linux
	if(libHandle != nullptr) {
        if(dlclose(libHandle) != 0) {
        	// cannot close library
        }
        libHandle = nullptr;
	}
#endif
}

esl::module::Module& Library::getModule() {
	if(libModule == nullptr) {
		libModule = &libGetModule();
	}
	return *libModule;
}

} /* namespace module */
} /* namespace esl */
