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

#ifndef ESL_OBJECT_OBJECTCONTEXT_H_
#define ESL_OBJECT_OBJECTCONTEXT_H_

#include <esl/object/Interface.h>

#include <set>
#include <string>
#include <memory>

namespace esl {
namespace object {

class ObjectContext : public virtual Interface::Object {
public:
	template<typename T = object::Interface::Object>
	T* findObject(const std::string& id) {
		return dynamic_cast<T*>(findRawObject(id));
	}

	template<typename T>
	const T* findObject(const std::string& id) const {
		return dynamic_cast<const T*>(findRawObject(id));
	}

	template<typename T = object::Interface::Object>
	void addObject(const std::string& id, std::unique_ptr<T> t) {
		addRawObject(id, std::unique_ptr<object::Interface::Object>(t.release()));
	}
	virtual std::set<std::string> getObjectIds() const = 0;

protected:
	virtual Interface::Object* findRawObject(const std::string& id) = 0;
	virtual const Interface::Object* findRawObject(const std::string& id) const = 0;
	virtual void addRawObject(const std::string& id, std::unique_ptr<Interface::Object> object) = 0;
};

} /* namespace object */
} /* namespace esl */

#endif /* ESL_OBJECT_OBJECTCONTEXT_H_ */
