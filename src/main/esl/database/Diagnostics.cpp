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

#include <esl/database/Diagnostics.h>

namespace esl {
namespace database {

const Diagnostic* Diagnostics::getSQLCode() const {
	const Diagnostic* rv = nullptr;

	for(std::vector<Diagnostic>::size_type i = 0; i < diagnostics.size(); ++i) {
		const Diagnostic& diagnostic = diagnostics[i];
        if(diagnostic.code == -99999 && (diagnostic.state == "xxxxx" || diagnostic.state == "01S02")) {
            continue;
        }
		if(rv == nullptr || rv->state < diagnostic.state) {
			rv = &diagnostic;
		}
	}
	return rv;
}

void Diagnostics::dump(std::ostream& stream) const {
	stream << "Dump " << diagnostics.size() << " diagnostics\n";
	for(std::vector<Diagnostic>::size_type i = 0; i < diagnostics.size(); ++i) {
		const Diagnostic& diagnostic = diagnostics[i];

		stream << "  SQLSTATE:           " << diagnostic.state << std::endl;
		stream << "  Nativer Fehlercode: " << diagnostic.code  << std::endl;
		stream << "    " << diagnostic.message << std::endl;
    }
}

void Diagnostics::dump(esl::logging::StreamReal& stream, esl::logging::Location location) const {
	stream(location.object, location.function, location.file, location.line) << "Dump " << diagnostics.size() << " diagnostics\n";
	for(std::vector<Diagnostic>::size_type i = 0; i < diagnostics.size(); ++i) {
		const Diagnostic& diagnostic = diagnostics[i];

		stream(location.object, location.function, location.file, location.line) << "  SQLSTATE:           " << diagnostic.state << std::endl;
		stream(location.object, location.function, location.file, location.line) << "  Nativer Fehlercode: " << diagnostic.code  << std::endl;
		stream(location.object, location.function, location.file, location.line) << "    " << diagnostic.message << std::endl;
    }
}

} /* namespace database */
} /* namespace esl */


