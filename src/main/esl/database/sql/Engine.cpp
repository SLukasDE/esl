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

#include <esl/database/sql/Engine.h>
#include <esl/object/Properties.h>
#include <esl/Module.h>

namespace esl {
namespace database {
namespace sql {

module::Implementation& Engine::getDefault() {
	static module::Implementation implementation;
	return implementation;
}

Engine::Engine(const Interface::Settings& settings, const std::string& implementation)
: engine(esl::getModule().getInterface<Interface>(implementation).createEngine(settings))
{ }

void Engine::addTables(const std::string& id, std::unique_ptr<table::Interface::Tables> tables) {
	engine->addTables(id, std::move(tables));
}

std::unique_ptr<database::Interface::ConnectionFactory> Engine::createConnectionFactory() {
	return engine->createConnectionFactory();
}

} /* namespace sql */
} /* namespace database */
} /* namespace esl */
