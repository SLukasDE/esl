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

#ifndef ESL_MODULE_LIBRARY_H_
#define ESL_MODULE_LIBRARY_H_

#include <esl/module/Module.h>

#include <string>
#include <set>

#define linux

namespace esl {
namespace module {

class Library {
public:
	static Library& load(std::string path);

	void install(Module& module);

	const std::string& getPath() const;
	void* getNativeHandle() const;

private:
	Library(void* nativeHandle, std::string path);
	~Library();

	void* nativeHandle = nullptr;
	const std::string path;
	static std::set<Library*> libraries;
};

} /* namespace module */
} /* namespace esl */

#endif /* ESL_MODULE_LIBRARY_H_ */
