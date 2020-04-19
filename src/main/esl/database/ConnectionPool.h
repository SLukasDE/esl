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

#ifndef ESL_DATABASE_CONNECTIONPOOL_H_
#define ESL_DATABASE_CONNECTIONPOOL_H_

#include <esl/database/Connection.h>
#include <esl/database/Interface.h>
#include <esl/utility/ObjectPool.h>
#include <chrono>

namespace esl {
namespace database {

class ConnectionPool : public Interface::ConnectionFactory {
public:
	using Strategy = esl::utility::ObjectPool<Connection>::Strategy;
	using CreateConnection = esl::utility::ObjectPool<Connection>::CreateObject;

	ConnectionPool(CreateConnection createConnection, unsigned int connectionsMax, std::chrono::milliseconds getTimeout, Strategy strategy, std::chrono::milliseconds connectionLifetime, bool resetTimeoutOnCreate, bool resetTimeoutOnDelete);
	~ConnectionPool() = default;

	//void addSetting(const std::string& key, const std::string& value) override;
	std::unique_ptr<Connection> createConnection() override;

private:
	esl::utility::ObjectPool<Connection> objectPool;
	std::chrono::milliseconds getTimeout;
	Strategy strategy;
};

} /* namespace database */
} /* namespace esl */

namespace esl {
namespace utility {
template<>
bool ObjectPool<esl::database::Connection>::isDirty(const esl::database::Connection& connection);
} /* namespace timer */
} /* namespace esl */

#endif /* ESL_DATABASE_CONNECTIONPOOL_H_ */
