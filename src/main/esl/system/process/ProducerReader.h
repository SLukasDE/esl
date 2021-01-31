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

#ifndef ESL_SYSTEM_PROCESS_PRODUCERREADER_H_
#define ESL_SYSTEM_PROCESS_PRODUCERREADER_H_

#include <esl/utility/Producer.h>
#include <esl/object/Values.h>
#include <esl/utility/Reader.h>
#include <esl/utility/Writer.h>
#include <esl/module/Implementation.h>

#include <initializer_list>
#include <string>
#include <memory>

namespace esl {
namespace system {
namespace process {

class ProducerReader : public utility::Producer {
public:
	static module::Implementation& getDefault();

	ProducerReader(utility::Reader& reader,
			std::initializer_list<std::pair<std::string, std::string>> settings,
			const std::string& implementation = getDefault().getImplementation());

	ProducerReader(utility::Reader& reader,
			const object::Values<std::string>& settings = getDefault().getSettings(),
			const std::string& implementation = getDefault().getImplementation());

	std::size_t write(utility::Writer& writer) override;

	utility::Reader* getReader() const noexcept;
	std::size_t getCurrentBufferSize() const noexcept;

private:
	static constexpr std::size_t maxBufferSize = 4096;
	std::size_t currentBufferSize = 0;
	char buffer[maxBufferSize];
	utility::Reader* reader;
};

} /* namespace process */
} /* namespace system */
} /* namespace esl */

#endif /* ESL_SYSTEM_PROCESS_PRODUCERREADER_H_ */