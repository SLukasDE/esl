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

#ifndef ESL_LOGGING_BUILTIN_LAYOUT_H_
#define ESL_LOGGING_BUILTIN_LAYOUT_H_

#include <esl/logging/layout/Interface.h>

namespace esl {
namespace logging {
namespace builtin {

class Layout : public layout::Interface::Layout {
public:
	static std::unique_ptr<layout::Interface::Layout> create(const layout::Interface::Settings& settings);

	static inline const char* getImplementation() {
		return "esl/logging/builtin";
	}

	std::string toString(const Location& location) const override;

	bool getShowTimestamp() const;
	bool getShowLevel() const;
	bool getShowTypeName() const;
	bool getShowAddress() const;
	bool getShowFile() const;
	bool getShowFunction() const;
	bool getShowLineNo() const;
	bool getShowThreadNo() const;

private:
	Layout(const layout::Interface::Settings& values);

	bool showTimestamp = true;
	bool showLevel = true;
	bool showTypeName = true;
	bool showAddress = true;
	bool showFile = false;
	bool showFunction = false;
	bool showLineNo = false;
	bool showThreadNo = true;
};

} /* namespace builtin */
} /* namespace logging */
} /* namespace esl */

#endif /* ESL_LOGGING_BUILTIN_LAYOUT_H_ */
