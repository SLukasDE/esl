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

#ifndef ESL_DATABASE_DIAGNOSTICS_H_
#define ESL_DATABASE_DIAGNOSTICS_H_

#include <esl/database/Diagnostic.h>
#include <esl/monitoring/Streams.h>

#include <ostream>
#include <vector>

namespace esl {
inline namespace v1_6 {
namespace database {

class Diagnostics {
public:
//	Diagnostics() = default;
//	virtual ~Diagnostics() = default;

	const Diagnostic* getSQLCode() const;

	void dump(std::ostream& stream) const;
	void dump(monitoring::Streams::Real& stream, monitoring::Streams::Location location = monitoring::Streams::Location{}) const;
	inline void dump(monitoring::Streams::Empty& stream, monitoring::Streams::Location location = monitoring::Streams::Location{}) const { };

protected:
	std::vector<Diagnostic> diagnostics;
};

} /* namespace database */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_DATABASE_DIAGNOSTICS_H_ */
