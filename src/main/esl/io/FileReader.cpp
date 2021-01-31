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


#include <esl/io/FileReader.h>
#include <esl/io/Interface.h>

namespace esl {
namespace io {

namespace {
std::unique_ptr<utility::Reader> createFileReader(const std::string& filename, const std::string& implementation, const object::Values<std::string>& settings) {
	std::unique_ptr<utility::Reader> rv;

	if(esl::getModule().getInterface<Interface>(implementation).createFileReader) {
		rv = esl::getModule().getInterface<Interface>(implementation).createFileReader(filename, settings);
	}

	return rv;
}
}

module::Implementation& FileReader::getDefault() {
	static module::Implementation implementation;
	return implementation;
}

FileReader::FileReader(const std::string& filename,
		std::initializer_list<std::pair<std::string, std::string>> settings,
		const std::string& implementation)
: fileReader(createFileReader(filename, implementation, object::ValueSettings(std::move(settings))))
{ }

FileReader::FileReader(const std::string& filename,
		const object::Values<std::string>& settings,
		const std::string& implementation)
: fileReader(createFileReader(filename, implementation, settings))
{ }

std::size_t FileReader::read(void* data, std::size_t size) {
	return npos;
}

utility::Reader* FileReader::getBaseImplementation() const noexcept {
	return fileReader.get();
}

} /* namespace io */
} /* namespace esl */
