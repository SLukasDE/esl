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

#ifndef ESL_OBJECT_PROCESSINGCONTEXT_H_
#define ESL_OBJECT_PROCESSINGCONTEXT_H_

#include <esl/object/ProcessingHandler.h>
#include <esl/object/Object.h>
#include <esl/object/Value.h>
#include <esl/object/Context.h>

#include <boost/filesystem/path.hpp>

#include <memory>
#include <string>
#include <vector>


namespace esl {
namespace object {

class ProcessingContext : public ProcessingHandler, public Context {
public:
	using ArgumentsByVector = Value<std::vector<std::string>>;
	using ReturnCodeObject = Value<int>;

	virtual void setParentObjectContext(esl::object::Context* aParentObject) = 0;

	virtual ProcessingContext& addData(const std::string& configuration) = 0;
	virtual ProcessingContext& addFile(const boost::filesystem::path& filename) = 0;

#ifdef ESL_1_6
/* TODO:
 * Rename method 'Context& addReference(const std::string& destinationId, const std::string& sourceId);'
 * to method     'Context& addAlias(const std::string& destinationId, const std::string& sourceId);'
 */
	virtual ProcessingContext& addAlias(const std::string& destinationId, const std::string& sourceId) = 0;
#else
	virtual ProcessingContext& addReference(const std::string& destinationId, const std::string& sourceId) = 0;
#endif
	virtual int getReturnCode() const = 0;

	/* From Event:
	 * -------------------
	 * virtual void onEvent(const Object& object) = 0;
	 */

	/* From Context:
	 * -------------------
	 * virtual std::set<std::string> getObjectIds() const = 0;
	 */

	/* From Procedure:
	 * ---------------
	 * virtual void procedureRun(Context& objectContext) = 0;
	 */

#ifdef ESL_1_6
/* TODO:
 * Following 2 add-Methods are unnecessary.
 *
 * § Instead of calling        'add(id, std::move(object));'
 *   just call existing method 'addObject(id, std::move(object));'
 *
 * § Instead of calling        'add(std::move(object));'
 *   just call existing method 'addObject("", std::move(object));'
 */
#else
	/* Helper methods */
	template<typename T = Object>
	ProcessingContext& add(const std::string& id, std::unique_ptr<T> t) {
		addRawObject(id, std::move(t));
		return *this;
	}

	template<typename T = Object>
	ProcessingContext& add(std::unique_ptr<T> t) {
		addRawObject("", std::move(t));
		return *this;
	}
#endif

#ifdef ESL_1_6
/* TODO:
 * Rename method 'Context& add(const std::string& sourceId);'
 * to method     'Context& addReference(const std::string& sourceId);'
 * if possible
 */
	ProcessingContext& addReference(const std::string& sourceId);
#else
	ProcessingContext& add(const std::string& sourceId);
#endif

	ProcessingContext& run(Context& objectContext);
	ProcessingContext& run(Context& objectContext, int argc, const char *argv[]);
	ProcessingContext& run();
	ProcessingContext& run(int argc, const char *argv[]);

	int main(Context& objectContext);
	int main(Context& objectContext, int argc, const char *argv[]);
	int main();
	int main(int argc, const char *argv[]);

protected:
	/* From Context:
	 * -------------------
	 * virtual Object* findRawObject(const std::string& id) = 0;
	 * virtual const Object* findRawObject(const std::string& id) const = 0;
	 * virtual void addRawObject(const std::string& id, std::unique_ptr<Object> object) = 0;
	 */
};

} /* namespace object */
} /* namespace esl */

#endif /* ESL_OBJECT_PROCESSINGCONTEXT_H_ */
