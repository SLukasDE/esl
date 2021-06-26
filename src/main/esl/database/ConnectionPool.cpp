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

#include <esl/database/ConnectionPool.h>
#include <esl/Stacktrace.h>

#include <stdexcept>

namespace esl {
namespace database {

namespace {

class CPConnection : public Connection {
public:
	CPConnection(esl::utility::ObjectPool<Connection>::unique_ptr connection);
	~CPConnection();

	PreparedStatement prepare(const std::string& sql) const override;
	ResultSet getTable(const std::string& tableName) override;

    void commit() const override;
    void rollback() const override;

    bool isClosed() const override;

	void* getNativeHandle() const override;

private:
    esl::utility::ObjectPool<Connection>::unique_ptr connection;
};

CPConnection::CPConnection(esl::utility::ObjectPool<Connection>::unique_ptr aConnection)
: connection(std::move(aConnection))
{
    if(!connection) {
    	throw esl::addStacktrace(std::runtime_error("connection is empty"));
    }
}

CPConnection::~CPConnection() {
}

void CPConnection::commit() const {
	connection->commit();
}

void CPConnection::rollback() const {
	connection->rollback();
}

bool CPConnection::isClosed() const {
	return connection->isClosed();
}


void* CPConnection::getNativeHandle() const {
	return connection->getNativeHandle();
}

//PreparedStatement& CPConnection::prepare(const std::string& sql) const {
PreparedStatement CPConnection::prepare(const std::string& sql) const {
	return connection->prepare(sql);
}

ResultSet CPConnection::getTable(const std::string& tableName) {
	return ResultSet();
}

} /* anonymous namespace */


ConnectionPool::ConnectionPool(CreateConnection createConnection, unsigned int connectionsMax, std::chrono::milliseconds aGetTimeout, Strategy aStrategy, std::chrono::milliseconds connectionLifetime, bool resetTimeoutOnCreate, bool resetTimeoutOnDelete)
: Interface::ConnectionFactory(),
  objectPool(createConnection, connectionsMax, connectionLifetime, resetTimeoutOnCreate, resetTimeoutOnDelete),
  getTimeout(aGetTimeout),
  strategy(aStrategy)
{
}

std::unique_ptr<Connection> ConnectionPool::createConnection() {
	esl::utility::ObjectPool<Connection>::unique_ptr connection(objectPool.get(getTimeout, strategy));

	if(connection) {
	    return std::unique_ptr<Connection>(new CPConnection(std::move(connection)));
	}

    return std::unique_ptr<Connection>(nullptr);
}

} /* namespace database */
} /* namespace esl */

template<>
bool esl::utility::ObjectPool<esl::database::Connection>::isDirty(const esl::database::Connection& connection) {
	return connection.isClosed();
}
