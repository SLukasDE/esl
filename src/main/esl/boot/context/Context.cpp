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

#include <esl/boot/context/Context.h>

namespace esl {
namespace boot {
namespace context {

module::Implementation& Context::getDefault() {
	static module::Implementation implementation;
	return implementation;
}

Context::Context(const std::vector<std::pair<std::string, std::string>>& settings, const std::string& implementation)
: context(getModule().getInterface<Interface>(implementation).create(settings))
{ }

Interface::Context& Context::addData(const std::string& configuration) {
	return context->addData(configuration);
}

Interface::Context& Context::addFile(const boost::filesystem::path& filename) {
	return context->addFile(filename);
}

Interface::Context& Context::addReference(const std::string& destinationId, const std::string& sourceId) {
	return context->addReference(destinationId, sourceId);
}

int Context::getReturnCode() const {
	return context->getReturnCode();
}

void Context::onEvent(const object::Interface::Object& object) {
	context->onEvent(object);
}

std::set<std::string> Context::getObjectIds() const {
	return context->getObjectIds();
}

void Context::procedureRun(object::Context& objectContext) {
	context->procedureRun(objectContext);
}

object::Interface::Object* Context::findRawObject(const std::string& id) {
	return context->findObject<object::Interface::Object>(id);
}

const object::Interface::Object* Context::findRawObject(const std::string& id) const {
	return context->findObject<object::Interface::Object>(id);
}

void Context::addRawObject(const std::string& id, std::unique_ptr<object::Interface::Object> object) {
	context->addObject(id, std::move(object));
}

} /* namespace context */
} /* namespace boot */
} /* namespace esl */
