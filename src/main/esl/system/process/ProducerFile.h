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

#ifndef ESL_SYSTEM_PROCESS_PRODUCERFILE_H_
#define ESL_SYSTEM_PROCESS_PRODUCERFILE_H_

#include <esl/system/Interface.h>
#include <esl/object/Values.h>

#include <initializer_list>
#include <string>
#include <memory>

namespace esl {
namespace system {
namespace process {

class ProducerFile : public Interface::ProducerFile {
public:
	static void setDefaultImplementation(std::string implementation);
	static const std::string& getDefaultImplementation();

	ProducerFile(std::string filename,
			std::initializer_list<std::pair<std::string, std::string>> values,
			const std::string& implementation = getDefaultImplementation());

	ProducerFile(std::string filename,
			const object::Values<std::string>& values,
			const std::string& implementation = getDefaultImplementation());

	std::size_t write(Interface::FileDescriptor& fileDescriptor) override;
	std::size_t getFileSize() const override;

private:
	std::unique_ptr<Interface::ProducerFile> producerFile;
};

} /* namespace process */
} /* namespace system */
} /* namespace esl */

#endif /* ESL_SYSTEM_PROCESS_PRODUCERFILE_H_ */
