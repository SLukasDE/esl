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

#include <esl/object/Properties.h>
#include <esl/Stacktrace.h>

#include <stdexcept>

namespace esl {
namespace object {

Properties::Properties(const Interface::Settings& aSettings)
: settings(aSettings),
  settingsMap(aSettings.begin(), aSettings.end())
{ }

void Properties::addValue(const std::string& key, const std::string& value) {
	settingsMap[key] = value;
	settings.push_back(std::make_pair(key, value));
}

bool Properties::hasValue(const std::string& key) const {
	return settingsMap.find(key) != settingsMap.end();
}

std::string Properties::getValue(const std::string& key) const {
	auto iter = settingsMap.find(key);
	if(iter == settingsMap.cend()) {
		throw esl::addStacktrace(std::runtime_error("Unknown parameter key=\"" + key + "\""));
	}
	return iter->second;
}

const std::vector<std::pair<std::string, std::string>>& Properties::getValues() const {
	return settings;
}

} /* namespace object */
} /* namespace esl */
