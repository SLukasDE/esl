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

#ifndef ESL_UTILITY_CONSUMER_H_
#define ESL_UTILITY_CONSUMER_H_

#include <esl/utility/Reader.h>

namespace esl {
namespace utility {

class Consumer {
public:
	Consumer() = default;
	virtual ~Consumer() = default;

	/* TODO: Methode sollte vielleicht in consume(...) umbenannt werden:
	 *       virtual std::size_t consume(Reader& reader) = 0;
	 *       -> In class Producer analog in producer(...)
	 */
	/* return: Reader::npos
	 *           if there is no more data to read or Consumer is not interested for reading more data
	 *
	 *         Number of characters read from Reader */
	/* TODO: Macht der Return-Type so Sinn?
	 *       Es sollte vermutlich ein "bool" sein.
	 *       -> Zu überprüfen mit esl::system::Process
	 *       -> Die Methode process(...) in esl::http::server::requesthandler::Interface::RequestHandler liefert bereits bool zurück.
	 *       -> Für esl::messaging::messagehandler::Interface::CreateMessageHandler würde bool reichen und es wird auch nur auf ==npos bzw !=npos überprüft.
	 *
	 *       Der Reader weiß, wieviel gelesen wurde.
	 *       Und derjenige, der DIESE read(consume)-Methode aufruft sollte nur wissen,
	 *       ob er diese read(consume)-Methode erneut aufrufen darf.
	 */
	virtual std::size_t read(Reader& reader) = 0;
};

} /* namespace utility */
} /* namespace esl */

#endif /* ESL_UTILITY_CONSUMER_H_ */
