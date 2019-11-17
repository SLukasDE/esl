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

#ifndef ESL_LOGGING_LAYOUT_H_
#define ESL_LOGGING_LAYOUT_H_

#include <esl/logging/Id.h>
#include <string>

namespace esl {
namespace logging {

class Layout {
public:
	Layout() = default;
	~Layout() = default;

	bool getShowTimestamp() const;
	void setShowTimestamp(bool showTimestamp = true);

	bool getShowLevel() const;
	void setShowLevel(bool showLevel = true);

	bool getShowTypeName() const;
	void setShowTypeName(bool showTypeName = true);

	bool getShowAddress() const;
	void setShowAddress(bool showAddress = true);

	bool getShowFile() const;
	void setShowFile(bool showFile = true);

	bool getShowFunction() const;
	void setShowFunction(bool showFunction = true);

	bool getShowLineNo() const;
	void setShowLineNo(bool showLineNo = true);

	bool getShowThreadNo() const;
	void setShowThreadNo(bool showThreadNo = true);

	std::string makePrefix(const Id& id);

private:
	bool showTimestamp = true;
	bool showLevel = true;
	bool showTypeName = true;
	bool showThreadNo = true;
	bool showAddress = true;
	bool showFunction = false;
	bool showFile = false;
	bool showLineNo = false;
};

} /* namespace logging */
} /* namespace esl */

#endif /* ESL_LOGGING_LAYOUT_H_ */
