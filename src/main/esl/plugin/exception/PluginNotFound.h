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

#ifndef ESL_PLUGIN_EXCEPTION_PLUGINNOTFOUND_H_
#define ESL_PLUGIN_EXCEPTION_PLUGINNOTFOUND_H_

#include <stdexcept>
#include <string>
#include <typeindex>

namespace esl {
namespace plugin {
namespace exception {

class PluginNotFound : public std::runtime_error {
public:
	PluginNotFound(std::type_index typeIndex);
	PluginNotFound(std::type_index typeIndex, const std::string& implementation);
	PluginNotFound(std::type_index typeIndex, const std::string& implementation, const char* message);
	PluginNotFound(std::type_index typeIndex, const std::string& implementation, const std::string& message);

	const std::string& getImplementation() const noexcept;
	std::type_index getTypeIndex() const noexcept;

private:
	const std::type_index typeIndex;
	const std::string implementation;
};

} /* namespace exception */
} /* namespace plugin */
} /* namespace esl */

#endif /* ESL_PLUGIN_EXCEPTION_PLUGINNOTFOUND_H_ */
