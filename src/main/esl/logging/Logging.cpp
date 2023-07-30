/*
MIT License
Copyright (c) 2019-2023 Sven Lukas

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

#include <esl/logging/Logging.h>
#include <esl/plugin/Registry.h>
#include <esl/system/Stacktrace.h>

#include <stdexcept>

namespace esl {
inline namespace v1_6 {
namespace logging {

void Logging::init() {
	init(plugin::Registry::get().create<Logging>());
}

void Logging::init(std::unique_ptr<Logging> aLogging) {
	plugin::Registry::setLogging(std::move(aLogging));
}

void Logging::init(const std::string& implementation, const std::vector<std::pair<std::string, std::string>>& settings) {
	std::unique_ptr<Logging> logging = plugin::Registry::get().create<Logging>(implementation, settings);
	if(!logging) {
		throw system::Stacktrace::add(std::runtime_error("Cannot create an logging plugin for implementation \"" + implementation + "\"."));
	}
	init(std::move(logging));
}

void Logging::initWithData(const std::string& configuration) {
	init();

	Logging* logging = get();
	if(!logging) {
		throw system::Stacktrace::add(std::runtime_error("Cannot create an logging plugin with data."));
	}
	logging->addData(configuration);
}

void Logging::initWithData(const std::string& configuration, std::unique_ptr<Logging> aLogging) {
	init(std::move(aLogging));

	Logging* logging = get();
	if(!logging) {
		throw system::Stacktrace::add(std::runtime_error("Cannot create an logging plugin with data."));
	}
	logging->addData(configuration);
}

void Logging::initWithData(const std::string& configuration, const std::string& implementation, const std::vector<std::pair<std::string, std::string>>& settings) {
	init(implementation, settings);

	Logging* logging = get();
	if(!logging) {
		throw system::Stacktrace::add(std::runtime_error("Cannot create an logging plugin with data for implementation \"" + implementation + "\"."));
	}
	logging->addData(configuration);
}

void Logging::initWithFile(const boost::filesystem::path& filename) {
	init();

	Logging* logging = get();
	if(!logging) {
		throw system::Stacktrace::add(std::runtime_error("Cannot create an logging plugin with file \"" + filename.string() + "\"."));
	}
	logging->addFile(filename);
}

void Logging::initWithFile(const boost::filesystem::path& filename, std::unique_ptr<Logging> aLogging) {
	init(std::move(aLogging));

	Logging* logging = get();
	if(!logging) {
		throw system::Stacktrace::add(std::runtime_error("Cannot create an logging plugin with file \"" + filename.string() + "\"."));
	}
	logging->addFile(filename);
}

void Logging::initWithFile(const boost::filesystem::path& filename, const std::string& implementation, const std::vector<std::pair<std::string, std::string>>& settings) {
	init(implementation, settings);

	Logging* logging = get();
	if(!logging) {
		throw system::Stacktrace::add(std::runtime_error("Cannot create an logging plugin with file \"" + filename.string() + "\" for implementation \"" + implementation + "\"."));
	}
	logging->addFile(filename);
}

Logging* Logging::get() {
	return plugin::Registry::getLogging();
}

} /* namespace logging */
} /* inline namespace v1_6 */
} /* namespace esl */
