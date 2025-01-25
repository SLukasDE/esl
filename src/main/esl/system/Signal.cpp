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

#include <esl/system/Signal.h>

namespace esl {
inline namespace v1_6 {
namespace utility {

template<>
const std::string& system::Signal::toString(system::SignalType signalType) noexcept {
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
	case system::SignalType::unknown:
		return strUnknown;
	case system::SignalType::hangUp:
		return strHangUp;
	case system::SignalType::interrupt:
		return strInterrupt;
	case system::SignalType::quit:
		return strQuit;
	case system::SignalType::ill:
		return strIll;
	case system::SignalType::trap:
		return strTrap;
	case system::SignalType::abort:
		return strAbort;
	case system::SignalType::busError:
		return strBusError;
	case system::SignalType::floatingPointException:
		return strFloatingPointException;
	case system::SignalType::segmentationViolation:
		return strSegmentationViolation;
	case system::SignalType::user1:
		return strUser1;
	case system::SignalType::user2:
		return strUser2;
	case system::SignalType::alarm:
		return strAlarm;
	case system::SignalType::child:
		return strChild;
	case system::SignalType::stackFault:
		return strStackFault;
	case system::SignalType::terminate:
		return strTerminate;
	case system::SignalType::pipe:
		return strPipe;
	case system::SignalType::kill:
		return strKill;
	}
	return strEmpty;
}

} /* namespace system */
} /* inline namespace v1_6 */
} /* namespace esl */
