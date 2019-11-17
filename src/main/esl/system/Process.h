/*
MIT License
Copyright (c) 2019 Sven Lukas

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

#ifndef ESL_SYSTEM_PROCESS_H_
#define ESL_SYSTEM_PROCESS_H_

#include <esl/system/Interface.h>
#include <string>
#include <list>
#include <memory>

namespace esl {
namespace system {

class Process /*: public Interface::Process*/ {
public:
    class Output/* : public Interface::ProcessOutput*/ {
    	friend class Process;
    public:
    	Output(Interface::Process::Output& aBase)
        : /*Interface::ProcessOutput(), */
		  base(aBase),
		  basePtr(&aBase)
    	{ }
    	~Output() = default;

    	std::size_t read(void* buffer, std::size_t s) /*override*/ {
    		return base.read(buffer, s);
    	}
    	bool setBlocking(bool blocking) /*override*/ {
    		return base.setBlocking(blocking);
    	}

    private:
    	Interface::Process::Output& base;
    	std::unique_ptr<Interface::Process::Output> basePtr;
    };

    Process();
    ~Process();

    void enableTimeMeasurement(bool enabled); // override;
    void setWorkingDirectory(const std::string& workingDirectory); // override;
    void setOutput(std::unique_ptr<Output> output, bool stdOut, bool stdErr); // override;
    Output* getStdOut() const; // override;
    Output* getStdErr() const; // override;

    /* return true on success */
    bool execute(const std::string& executable, const std::list<std::string>& arguments); // override;

    int wait(); // override;
    bool isRunning(); // override;
    bool isFailed(); // override;

    unsigned int getTimeRealMS() const; // override;
    unsigned int getTimeUserMS() const; // override;
    unsigned int getTimeSysMS() const; // override;

private:
    Interface::Process& process;
    std::unique_ptr<Output> outErr;
    std::unique_ptr<Output> err;

    Output* outPtr = nullptr;
    Output* errPtr = nullptr;
};

} /* namespace system */
} /* namespace esl */

#endif /* ESL_SYSTEM_PROCESS_H_ */
