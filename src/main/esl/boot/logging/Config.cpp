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

#include <esl/boot/logging/Config.h>
#include <esl/boot/logging/IConfig.h>
#include <esl/plugin/Plugin.h>
#include <esl/plugin/Registry.h>

namespace esl {
namespace boot {
namespace logging {

void Config::loadData(const std::string& configuration) {
	const IConfig::Plugin* plugin = plugin::Registry::get().findPlugin<IConfig::Plugin>();
	if(!plugin) {
		throw std::runtime_error("Cannot find plugin for esl::boot::IConfig");
	}

	std::unique_ptr<IConfig> config = plugin->create({});
	if(!config) {
		throw std::runtime_error("Plugin for esl::boot::IConfig does not create an oboject");
	}

	config->loadData(configuration);
}

void Config::loadFile(const boost::filesystem::path& filename) {
	const IConfig::Plugin* plugin = plugin::Registry::get().findPlugin<IConfig::Plugin>();
	if(!plugin) {
		throw std::runtime_error("Cannot find plugin for esl::boot::IConfig");
	}

	std::unique_ptr<IConfig> config = plugin->create({});
	if(!config) {
		throw std::runtime_error("Plugin for esl::boot::IConfig does not create an oboject");
	}

	config->loadFile(filename);
}

} /* namespace logging */
} /* namespace boot */
} /* namespace esl */
