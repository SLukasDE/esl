/*
MIT License
Copyright (c) 2019-2025 Sven Lukas

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

#ifndef ESL_OBJECT_PROCESSINGHANDLER_H_
#define ESL_OBJECT_PROCESSINGHANDLER_H_

#include <esl/com/common/server/RequestHandler.h>
#include <esl/object/Procedure.h>

namespace esl {
inline namespace v1_6 {
namespace object {

/* TODO: Braucht man den Typ?
 *       Oder käme man nicht aus mit com::common::server::RequestHandler ?
 *
 * Statt:
 * class ProcessingContext : public Context, public ProcessingHandler { ... }
 *
 * Müsste es dann heißen:
 * class ProcessingContext : public Context, public Procedure, public com::common::server::RequestHandler { ... }
 *
 */
struct ProcessingHandler : public com::common::server::RequestHandler, public Procedure { };

} /* namespace object */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_OBJECT_PROCESSINGHANDLER_H_ */
