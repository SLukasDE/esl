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

#ifndef ESL_IO_PRODUCER_H_
#define ESL_IO_PRODUCER_H_

#include <esl/io/Writer.h>

namespace esl {
namespace io {

class Producer {
public:
	Producer() = default;
	virtual ~Producer() = default;

	/* return: Writer::npos
	 *           if there is no more data to produce (IMPORTANT)
	 *
	 *         Number of characters written to fileDescriptor
	 *           if there are data available to write to fileDescripor
	 *           (produced now or queued from previous call). */
	/* TODO: Macht der Return-Type so Sinn?
	 *       Es sollte vermutlich ein "bool" sein.
	 *       -> Zu überprüfen mit esl::system::Process
	 */
	virtual std::size_t produce(Writer& writer) = 0;
};

} /* namespace io */
} /* namespace esl */

#endif /* ESL_IO_PRODUCER_H_ */
