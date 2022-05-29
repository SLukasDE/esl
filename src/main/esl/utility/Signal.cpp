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

#include <esl/utility/Signal.h>

namespace esl {
namespace utility {

template<>
const std::string& Signal::toString(SignalType signalType) noexcept {
	static const std::string strEmpty;
	static const std::string strUnknown = "unknown";
	static const std::string strHangUp = "hangUp";
	static const std::string strInterrupt = "interrupt";
	static const std::string strQuit = "quit";
	static const std::string strIll = "ill";
	static const std::string strTrap = "trap";
	static const std::string strAbort = "abort";
	static const std::string strBusError = "busError";
	static const std::string strFloatingPointException = "floatingPointException";
	static const std::string strSegmentationViolation = "segmentationViolation";
	static const std::string strUser1 = "user1";
	static const std::string strUser2 = "user2";
	static const std::string strAlarm = "alarm";
	static const std::string strChild = "child";
	static const std::string strStackFault = "stackFault";
	static const std::string strTerminate = "terminate";
	static const std::string strPipe = "pipe";
	static const std::string strKill = "kill";

	switch(signalType) {
	case unknown:
		return strUnknown;
	case hangUp:
		return strHangUp;
	case interrupt:
		return strInterrupt;
	case quit:
		return strQuit;
	case ill:
		return strIll;
	case trap:
		return strTrap;
	case abort:
		return strAbort;
	case busError:
		return strBusError;
	case floatingPointException:
		return strFloatingPointException;
	case segmentationViolation:
		return strSegmentationViolation;
	case user1:
		return strUser1;
	case user2:
		return strUser2;
	case alarm:
		return strAlarm;
	case child:
		return strChild;
	case stackFault:
		return strStackFault;
	case terminate:
		return strTerminate;
	case pipe:
		return strPipe;
	case kill:
		return strKill;
	}
	return strEmpty;
}

} /* namespace utility */
} /* namespace esl */
