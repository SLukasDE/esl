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

#include <esl/logging/Layout.h>
#include <esl/Module.h>

namespace esl {
namespace logging {

namespace {
std::unique_ptr<layout::Interface::Layout> createLayout(const layout::Interface::Settings& settings, const std::string& implementation) {
	const layout::Interface* interface = esl::getModule().findInterface<layout::Interface>(implementation);
	return interface ? interface->createLayout(settings) : nullptr;
}
}

module::Implementation& Layout::getDefault() {
	static module::Implementation implementation;
	return implementation;
}

/*
Layout::Layout(std::initializer_list<std::pair<std::string, std::string>> aSettings, const std::string& aImplementation)
: implementation(aImplementation),
  settings(std::move(aSettings))
{ }
*/

Layout::Layout(const layout::Interface::Settings& aSettings, const std::string& aImplementation)
: implementation(aImplementation),
  settings(std::move(aSettings))
{ }

std::string Layout::toString(const Location& location) const {
	if(!layout) {
		layout = createLayout(settings, implementation);
	}
	if(layout) {
		return layout->toString(location);
	}
	return "";
}

} /* namespace esl */
} /* namespace logging */
