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

#include <esl/system/Arguments.h>
#include <esl/utility/String.h>

#include <vector>
#include <cstring>

namespace esl {
namespace system {

Arguments::Arguments(const Arguments& other)
: args(other.args),
  argc(other.argc)
{
	if(argc == 0) {
		return;
	}

	argv = new char*[argc + 1];
	for(std::size_t i = 0; i<argc; ++i) {
		std::size_t length = std::strlen(other.argv[i]);
		argv[i] = new char[length + 1];
		std::memcpy(argv[i], other.argv[i], length + 1);
	}
	argv[argc] = nullptr;
}


Arguments::Arguments(Arguments&& other)
: args(std::move(other.args)),
  argc(other.argc),
  argv(other.argv)
{
	other.argc = 0;
	other.argv = nullptr;
}

Arguments::Arguments(std::string aArgs)
: args(esl::utility::String::trim(std::move(aArgs), ' '))
{
	std::vector<char*> arguments;

    for(const char* src = args.c_str(); *src != 0; ++argc) {
		std::size_t length;

		argumentSize(src, length);
		arguments.push_back(new char[length + 1]);
        src = argumentCopy(src, arguments[argc]);
	}

	if(argc == 0) {
		return;
	}

	argv = new char*[argc + 1];
	for(std::size_t i = 0; i<argc; ++i) {
		argv[i] = arguments[i];
	}
	argv[argc] = nullptr;
}

Arguments::Arguments(std::size_t aArgc, const char** aArgv)
: argc(aArgc)
{
	if(argc == 0) {
		return;
	}

	argv = new char*[argc + 1];
	for(std::size_t i = 0; i<argc; ++i) {
		/* TODO:
		 * Actually this is wrong!
		 * We have to escape the characters '\' and ' '.
		 */
		std::size_t length = std::strlen(aArgv[i]);
		argv[i] = new char[length + 1];
		argv[i][0] = 0;
		std::strncat(argv[i], aArgv[i], length);

		if(i > 0) {
			args += " ";
		}
		args += argv[i];
	}
	argv[argc] = nullptr;
}

Arguments::~Arguments() {
    for(std::size_t i = 0; i<argc; ++i) {
    	delete[] argv[i];
    }
    if(argv) {
    	delete[] argv;
    }
}

Arguments& Arguments::operator=(const Arguments& other) {
	if(this != &other) {
		/* first delete own entries */
	    for(std::size_t i = 0; i<argc; ++i) {
	    	delete[] argv[i];
	    }
	    if(argv) {
	    	delete[] argv;
	    }

		/* now copy entries */
		args = other.args;
		argc = other.argc;
		if(argc == 0) {
			argv = nullptr;
		}
		else {
			argv = new char*[argc + 1];
			for(std::size_t i = 0; i<argc; ++i) {
				std::size_t length = std::strlen(other.argv[i]);
				argv[i] = new char[length + 1];
				std::memcpy(argv[i], other.argv[i], length + 1);
			}
			argv[argc] = nullptr;
		}
	}

	return *this;
}

Arguments& Arguments::operator=(Arguments&& other) {
	if(this != &other) {
		/* first delete own entries */
	    for(std::size_t i = 0; i<argc; ++i) {
	    	delete[] argv[i];
	    }
	    if(argv) {
	    	delete[] argv;
	    }

		/* now move entries */
		args = std::move(other.args);
		argc = other.argc;
		argv = other.argv;

		other.argc = 0;
		other.argv = nullptr;
	}

	return *this;
}

const std::string& Arguments::getArgs() const noexcept {
	return args;
}

std::size_t Arguments::getArgc() const noexcept {
	return argc;
}

char** Arguments::getArgv() const noexcept {
	return argv;
}

const char* Arguments::argumentSize(const char* src, std::size_t& length) {
	length = 0;

	for(;*src != 0; ++src) {
		if(*src == ' ') {
			while(*src == ' ') {
				++src;
			}
			break;
		}

		if(*src == '\\') {
			++src;
			if(*src == 0) {
				break;
			}
		}

		++length;
	}

	return src;
}

const char* Arguments::argumentCopy(const char* src, char* dst) {
	for(;*src != 0; ++src) {
		if(*src == ' ') {
			while(*src == ' ') {
				++src;
			}
			break;
		}

		if(*src == '\\') {
			++src;
			if(*src == 0) {
				break;
			}
		}

		*dst = *src;
		++dst;
	}

	*dst = 0;
	return src;
}

} /* namespace system */
} /* namespace esl */
