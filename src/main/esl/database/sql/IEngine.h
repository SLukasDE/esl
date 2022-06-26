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

#ifndef ESL_DATABASE_SQL_IENGINE_H_
#define ESL_DATABASE_SQL_IENGINE_H_

#include <esl/database/IConnectionFactory.h>
#include <esl/database/table/ITables.h>
#include <esl/object/IObject.h>
#include <esl/plugin/Plugin.h>

#include <memory>

namespace esl {
namespace database {
namespace sql {

class IEngine : public virtual object::IObject {
public:
	using Plugin = plugin::Plugin<IEngine>;

	virtual void addTables(const std::string& id, std::unique_ptr<table::ITables> tables) = 0;
	virtual std::unique_ptr<IConnectionFactory> createConnectionFactory() = 0;
};

} /* namespace sql */
} /* namespace database */
} /* namespace esl */

#endif /* ESL_DATABASE_SQL_IENGINE_H_ */