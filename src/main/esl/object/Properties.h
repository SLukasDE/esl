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

#ifndef ESL_OBJECT_PROPERTIES_H_
#define ESL_OBJECT_PROPERTIES_H_

//#include <esl/object/Interface.h>
#include <esl/object/Values.h>

#include <string>
#include <utility>
#include <map>

namespace esl {
namespace object {

//class Properties : public Interface::Object {
class Properties : public esl::object::Values<std::string> {
public:
	Properties(const Interface::Settings& settings = {});

	void addValue(const std::string& key, const std::string& value);

	bool hasValue(const std::string& key) const override;
	std::string getValue(const std::string& key) const override;
	const std::vector<std::pair<std::string, std::string>>& getValues() const override;

private:
	Interface::Settings settings;
	std::map<std::string, std::string> settingsMap;
};

} /* namespace object */
} /* namespace esl */

#endif /* ESL_OBJECT_PROPERTIES_H_ */
