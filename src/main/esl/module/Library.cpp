/*
MIT License
Copyright (c) 2019-2021 Sven Lukas

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
//#include <esl/Module.h>
#include <esl/Stacktrace.h>

#include <stdexcept>
#include <memory>

#ifdef linux
#include <dlfcn.h>
#endif

namespace esl {
namespace module {

std::set<Library*> Library::libraries;

Library& Library::load(std::string path) {
	void* nativeHandle = nullptr;

#ifdef linux
	nativeHandle = dlopen(path.c_str(), RTLD_NOLOAD | RTLD_NOW | RTLD_LOCAL );
    if(nativeHandle != nullptr) {
       	throw std::runtime_error("Library loaded already");
    }

	nativeHandle = dlopen(path.c_str(), RTLD_NOW | RTLD_LOCAL );
    if(nativeHandle == nullptr) {
    	throw std::runtime_error(dlerror());
    }
#else
    if(nativeHandle == nullptr) {
       	throw std::runtime_error("Library loader not implemented so far");
    }
#endif

    Library* library = new Library(nativeHandle, std::move(path));
    libraries.insert(library);
    return *library;
}

void Library::install(Module& module) {
	using Install = void(*)(Module*);
	Install libInstall = nullptr;

#ifdef linux
    libInstall = reinterpret_cast<Install>(dlsym(nativeHandle, "esl__module__library__install"));
#else
   	throw std::runtime_error("Library loader not implemented so far");
#endif

    if(libInstall == nullptr) {
    	throw std::runtime_error("Symbol \"esl__module__library__install\" in library \"" + path + "\" is null");
    }
	libInstall(&module);
}

const std::string& Library::getPath() const {
	return path;
}

void* Library::getNativeHandle() const {
	return nativeHandle;
}

Library::Library(void* aNativeHandle, std::string aPath)
: nativeHandle(aNativeHandle),
  path(std::move(aPath))
{
    if(nativeHandle == nullptr) {
    	throw std::runtime_error("Cannot initialize library with empty nativeHandle");
    }
}

Library::~Library() {
#ifdef linux
    if(dlclose(nativeHandle) != 0) {
    	// cannot close library
    }
#endif
}

} /* namespace module */
} /* namespace esl */
