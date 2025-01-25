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

#ifndef ESL_OBJECT_CONTEXT_H_
#define ESL_OBJECT_CONTEXT_H_

#include <esl/object/Object.h>
#include <esl/system/Stacktrace.h>

#include <memory>
#include <set>
#include <stdexcept>
#include <string>

namespace esl {
inline namespace v1_6 {
namespace object {

class Context : public virtual Object {
public:
	virtual void addObject(const std::string& id, std::unique_ptr<Object> object) = 0;

	template<typename T = Object>
	T* findObject(const std::string& id) {
		return dynamic_cast<T*>(findRawObject(id));
	}

	template<typename T = Object>
	const T* findObject(const std::string& id) const {
		return dynamic_cast<const T*>(findRawObject(id));
	}

	template<typename T = Object>
	T& getObject(const std::string& id) {
		T* t = dynamic_cast<T*>(&getRawObject(id));
		if(!t) {
			throw system::Stacktrace::add(std::runtime_error("Failed to get object with id \"" + id + "\" because requested type is wrong"));
		}
		return *t;
	}

	template<typename T = Object>
	const T& getObject(const std::string& id) const {
		const T* t = dynamic_cast<const T*>(&getRawObject(id));
		if(!t) {
			throw system::Stacktrace::add(std::runtime_error("Failed to get object with id \"" + id + "\" because requested type is wrong"));
		}
		return *t;
	}

	virtual std::set<std::string> getObjectIds() const = 0;

protected:
	virtual Object* findRawObject(const std::string& id) = 0;
	virtual const Object* findRawObject(const std::string& id) const = 0;

	Object& getRawObject(const std::string& id) {
		Object* object = findRawObject(id);
		if(!object) {
			throw system::Stacktrace::add(std::runtime_error("Cannot get object with unknown id \"" + id + "\""));
		}
		return *object;
	}

	const Object& getRawObject(const std::string& id) const {
		const Object* object = findRawObject(id);
		if(!object) {
			throw system::Stacktrace::add(std::runtime_error("Cannot get object with unknown id \"" + id + "\""));
		}
		return *object;
	}
};

} /* namespace object */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_OBJECT_CONTEXT_H_ */
