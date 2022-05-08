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

#ifndef ESL_LOGGING_APPENDER_APPENDER_H_
#define ESL_LOGGING_APPENDER_APPENDER_H_

#include <esl/logging/appender/Interface.h>
#include <esl/module/Implementation.h>
#include <esl/module/Interface.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace esl {
namespace logging {
namespace appender {

class Appender : public Interface::Appender {
public:
	static module::Implementation& getDefault();

	Appender(const std::vector<std::pair<std::string, std::string>>& settings = getDefault().getSettings(),
			const std::string& implementation = getDefault().getImplementation());

	void setLayout(const layout::Interface::Layout* aLayout) override;
	const layout::Interface::Layout* getLayout() const override;

	/* both methods are NOT thread-safe */
	void setRecordLevel(RecordLevel aRecordLevel = RecordLevel::SELECTED) override;
	RecordLevel getRecordLevel() const override;

//protected:
	void flush() override;
	void flush(std::ostream& oStream) override;
	void write(const Location& location, const char* ptr, std::size_t size) override;

private:
	std::unique_ptr<Interface::Appender> appender;
};

} /* namespace appender */
} /* namespace logging */
} /* namespace esl */

#endif /* ESL_LOGGING_APPENDER_APPENDER_H_ */
