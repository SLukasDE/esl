/*
MIT License
Copyright (c) 2019-2025 Sven Lukas

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

#include <esl/plugin/Library.h>
#include <esl/plugin/Registry.h>

#include <memory>
#include <stdexcept>

#ifdef __linux__
#include <dlfcn.h>
#endif

namespace esl {
inline namespace v1_6 {
namespace plugin {


Library::Library(std::string aPath)
: path(std::move(aPath))
{
#ifdef __linux__
	void* testNativeHandle = dlopen(path.c_str(), RTLD_NOLOAD | RTLD_NOW | RTLD_LOCAL );
    if(testNativeHandle != nullptr) {
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
}

Library::~Library() {
#ifdef __linux__
    if(dlclose(nativeHandle) != 0) {
    	// cannot close library
    }
#endif
}

void* Library::getNativeHandle() const noexcept {
	return nativeHandle;
}

const std::string& Library::getPath() const noexcept {
	return path;
}

void Library::install(Registry& registry, const char* data) {
	using Install = void(*)(Registry*, const char*);
	Install libInstall = nullptr;

#ifdef __linux__
    libInstall = reinterpret_cast<Install>(dlsym(nativeHandle, "esl__plugin__library__install"));
#else
   	throw std::runtime_error("Library loader not implemented so far");
#endif

    if(libInstall == nullptr) {
    	throw std::runtime_error("Symbol \"esl__plugin__library__install\" in library \"" + path + "\" is null");
    }
	libInstall(&registry, data);
}

} /* namespace plugin */
} /* inline namespace v1_6 */
} /* namespace esl */
