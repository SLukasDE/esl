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

#ifndef ESL_OBJECT_VALUES_H_
#define ESL_OBJECT_VALUES_H_

#include <esl/object/Interface.h>
#include <esl/Stacktrace.h>

#include <vector>
#include <utility>
#include <stdexcept>

namespace esl {
namespace object {

template<typename T>
class Values : public virtual Interface::Object {
public:
	virtual bool hasValue(const std::string& key) {
		return false;
	}

	virtual T getValue(const std::string& key) {
		throw esl::addStacktrace(std::runtime_error("Unknown parameter key=\"" + key + "\""));
	}

	virtual std::vector<std::pair<std::string, T>> getValues() {
		return std::vector<std::pair<std::string, T>>();
	}
};

} /* namespace object */
} /* namespace esl */

#endif /* ESL_OBJECT_VALUES_H_ */
