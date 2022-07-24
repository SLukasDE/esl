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

#ifndef ESL_PROCESSING_CONTEXT_H_
#define ESL_PROCESSING_CONTEXT_H_

#include <esl/object/Event.h>
#include <esl/object/Object.h>
#include <esl/object/Value.h>
#include <esl/object/Context.h>
#include <esl/processing/Procedure.h>

#include <boost/filesystem/path.hpp>

#include <memory>
#include <string>
#include <vector>

namespace esl {
namespace processing {

class Context : public object::Event, public object::Context, public Procedure {
public:
	using ArgumentsByVector = object::Value<std::vector<std::string>>;
	using ReturnCodeObject = object::Value<int>;

	virtual Context& addData(const std::string& configuration) = 0;
	virtual Context& addFile(const boost::filesystem::path& filename) = 0;
	virtual Context& addReference(const std::string& destinationId, const std::string& sourceId) = 0;
	virtual int getReturnCode() const = 0;

	/* From Event:
	 * -------------------
	 * virtual void onEvent(const object::Object& object) = 0;
	 */

	/* From Context:
	 * -------------------
	 * virtual std::set<std::string> getObjectIds() const = 0;
	 */

	/* From Procedure:
	 * ---------------
	 * virtual void procedureRun(object::Context& objectContext) = 0;
	 */

	/* Helper methods */
	template<typename T = object::Object>
	Context& add(const std::string& id, std::unique_ptr<T> t) {
		addRawObject(id, std::move(t));
		return *this;
	}

	template<typename T = object::Object>
	Context& add(std::unique_ptr<T> t) {
		addRawObject("", std::move(t));
		return *this;
	}

	Context& add(const std::string& id);

	Context& run(object::Context& objectContext);
	Context& run(object::Context& objectContext, int argc, const char *argv[]);
	Context& run();
	Context& run(int argc, const char *argv[]);

	int main(object::Context& objectContext);
	int main(object::Context& objectContext, int argc, const char *argv[]);
	int main();
	int main(int argc, const char *argv[]);

protected:
	/* From Context:
	 * -------------------
	 * virtual object::Object* findRawObject(const std::string& id) = 0;
	 * virtual const object::Object* findRawObject(const std::string& id) const = 0;
	 * virtual void addRawObject(const std::string& id, std::unique_ptr<object::Object> object) = 0;
	 */
};

} /* namespace processing */
} /* namespace esl */

#endif /* ESL_PROCESSING_CONTEXT_H_ */
