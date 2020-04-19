/*
MIT License
Copyright (c) 2019, 2020 Sven Lukas

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

#ifndef ESL_DATABASE_CONNECTION_H_
#define ESL_DATABASE_CONNECTION_H_

#include <esl/database/PreparedStatement.h>
#include <memory>
#include <string>

namespace esl {
namespace database {

class Connection {
public:
	Connection() = default;
	virtual ~Connection() = default;

	virtual PreparedStatement prepare(const std::string& sql) const = 0;

	virtual void commit() const = 0;
	virtual void rollback() const = 0;

//    virtual void close() = 0;
	virtual bool isClosed() const = 0;

};

} /* namespace database */
} /* namespace esl */

#endif /* ESL_DATABASE_CONNECTION_H_ */

