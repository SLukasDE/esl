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

#include <esl/system/process/Environment.h>

#include <cstring>

namespace esl {
namespace system {
namespace process {

Environment::Environment()
: envc(0),
  envp(new char*[1])
{
    envp[envc] = nullptr;
}

Environment::Environment(Environment&& other)
: values(std::move(other.values)),
  envc(other.envc),
  envp(other.envp)
{
	other.envc = 0;
	other.envp = nullptr;
}

Environment::Environment(std::vector<std::pair<std::string, std::string>> aValues)
: values(std::move(aValues)),
  envc(values.size()),
  envp(new char*[envc + 1])
{
    for(std::size_t i=0; i<envc; ++i) {
    	std::string entry = values[i].first + "=" + values[i].second;
		envp[i] = new char[entry.size() + 1];
		envp[i][0] = 0;
		std::strncat(envp[i], entry.c_str(), entry.size());
    }
    envp[envc] = nullptr;
}

Environment::~Environment() {
    for(std::size_t i = 0; i<envc; ++i) {
    	delete[] envp[i];
    }
    if(envp) {
    	delete[] envp;
    }
}

Environment& Environment::operator=(Environment&& other) {
	values = std::move(other.values);

	if(this != &other) {
		/* first delete own entries */
	    for(std::size_t i = 0; i<envc; ++i) {
	    	delete[] envp[i];
	    }
	    if(envp) {
	    	delete[] envp;
	    }

		/* now move entries */
		envc = other.envc;
		envp = other.envp;

		other.envc = 0;
		other.envp = nullptr;
	}

	return *this;
}

const std::vector<std::pair<std::string, std::string>>& Environment::getValues() const noexcept {
	return values;
}

char* const* Environment::getEnvp() const noexcept {
	return envp;
}

} /* namespace process */
} /* namespace system */
} /* namespace esl */
