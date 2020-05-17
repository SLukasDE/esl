/*
MIT License
Copyright (c) 2019, 2020 Sven Lukas

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

#ifndef ESL_MODULE_MODULE_H_
#define ESL_MODULE_MODULE_H_

#include <esl/module/Interface.h>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <set>

#define DO_QUOTE(X)                  #X
#define QUOTE(X)                     DO_QUOTE(X)

#ifndef TRANSFORMER_ARTEFACT_ID
#define TRANSFORMER_ARTEFACT_ID
//#define TRANSFORMER_ARTEFACT_ID           esl
#endif

#ifndef TRANSFORMER_ARTEFACT_NAME
#define TRANSFORMER_ARTEFACT_NAME
//#define TRANSFORMER_ARTEFACT_NAME         esl
#endif

#ifndef TRANSFORMER_ARTEFACT_VERSION
#define TRANSFORMER_ARTEFACT_VERSION
//#define TRANSFORMER_ARTEFACT_VERSION      1.0.0
#endif

#ifndef TRANSFORMER_ARTEFACT_API_VERSION
#define TRANSFORMER_ARTEFACT_API_VERSION
//#define TRANSFORMER_ARTEFACT_API_VERSION  1
#endif

#ifndef TRANSFORMER_ARTEFACT_VARIANT
#define TRANSFORMER_ARTEFACT_VARIANT
#endif

#ifndef TRANSFORMER_ARTEFACT_ARCHITECTURE
#define TRANSFORMER_ARTEFACT_ARCHITECTURE
#endif

#ifndef TRANSFORMER_ARTEFACT_LICENSE
#define TRANSFORMER_ARTEFACT_LICENSE
#endif

namespace esl {
namespace module {

class Module {
	friend class Library;
public:
	Module() = default;
	virtual ~Module() = default;

	const std::string& getId() const;
	const std::string& getName() const;
	const std::string& getVariant() const;
	const std::string& getVersion() const;
	const std::string& getApiVersion() const;
	const std::string& getArchitecture() const;
	const std::string& getLicense() const;

	static inline void initialize(Module& module) {
		module.id = QUOTE(TRANSFORMER_ARTEFACT_ID);
		module.name = QUOTE(TRANSFORMER_ARTEFACT_NAME);
		module.variant = QUOTE(TRANSFORMER_ARTEFACT_VARIANT);
		module.version = QUOTE(TRANSFORMER_ARTEFACT_VERSION);
		module.apiVersion = QUOTE(TRANSFORMER_ARTEFACT_API_VERSION);
		module.architecture = QUOTE(TRANSFORMER_ARTEFACT_ARCHITECTURE);
		module.license = QUOTE(TRANSFORMER_ARTEFACT_LICENSE);
	}

	const std::vector<Interface>& getMetaInterfaces() const;

	const Interface* findInterface(const Interface& descriptor) const;

	template <class T>
	const T* findInterface(const std::string& implementationName = "");

	template <class T>
	const T& getInterface(const std::string& implementationName = "");

	//virtual Module* getModule(const std::string& module);
	void addInterfaces(const Module& foreignModule, const std::string& type = "", const std::string& implementation = "");
	void replaceInterfaces(const Module& foreignModule, const std::string& type = "", const std::string& implementation = "");

protected:
	void addInterface(std::unique_ptr<const Interface> interface);

private:
	std::string id;
	std::string name;
	std::string variant;
	std::string version;
	std::string apiVersion;
	std::string architecture;
	std::string license;

	/* Only contains interfaces owned by this module */
	std::vector<std::unique_ptr<const Interface>> ownInterfaces;

	/* ******************************************************** *
	 * ALL following containers store ALL interfaces:           *
	 * - owned interfaces (stored in interfaces) and            *
	 * - foreign interfaces (linked in e.g. my addModule(...)). *
	 * ******************************************************** */

	/* Contains meta interfaces by descending order.
	 * This container is used for quick execution of method getMetaInterfaces().
	 */
	std::vector<Interface> metaInterfaces;

	/* Contains addresses of interfaces by descending order.
	 * Method "addOrReplaceModule(...)" uses this container of the foreign module to insert interfaces into this module by the right order.
	 */
	std::vector<const Interface*> allInterfaces;

	/* Contains addresses.
	 * This container is used to make a quick check if address exists already.
	 */
	std::set<const Interface*> interfacesByAddress;

	/* used by addInterface(const Interface& newInterface, bool doReplace) to check if compatible interface exists already. */
	Interface* findMetaInterface(const std::string& type, const std::string& implementation);

	/* Used by addInterfaces(...) and replaceInterfaces(...) */
	void addOrReplaceInterfaces(const Module& foreignModule, const std::string& type, const std::string& implementation, bool doReplace);

	/* Insert or replace interface address and metaInterface.
	 * To replace an potential existing interface with the new one you have to set doReplace to true.
	 *
	 * If interface address does not exists already
	 * and interface type and interface implementation does not exist already there is no different if you set doReplace to false or true.
	 *
	 * If address exists already nothing will be changed in the module and false is returned.
	 *
	 * If interface type and interface implementation exist already behavior depends on doReplace.
	 * If doReplace is set to false then nothing will be changed in the object and false is returned.
	 * If doReplace is set to true then following containers (or elements in containers) will be updated:
	 * - metaInterfaces (matching metaInterface is updated to new metaInterface)
	 * - allInterfaces (matching element is updated to new address)
	 * - interfacesByAddress (old matching address is removed and new address is inserted)
	 *
	 * If insertion was successful true is returned.
	 */
	bool addInterface(const Interface& interface, bool doReplace);
};

template <class T>
const T* Module::findInterface(const std::string& implementationName) {
	static std::map<std::string, std::pair<bool, const T*>> implementations;
	static std::pair<bool, const T*> implementation{false, nullptr};

	std::pair<bool, const T*>& implementationEntry = implementationName.empty() ? implementation : implementations[implementationName];

	if(implementationEntry.first == false) {
		implementationEntry.first = true;
		implementationEntry.second = static_cast<const T*>(findInterface(Interface("", T::getType(), implementationName, T::getApiVersion())));
	}

	return implementationEntry.second;
}

template <class T>
const T& Module::getInterface(const std::string& implementationName) {
	const T* interface = findInterface<T>(implementationName);

	if(interface == nullptr) {
		if(implementationName.empty()) {
			throw std::runtime_error("no implementation available for type \"" + std::string(T::getType()) + "\" in module \"" + getName() + "\"");
		}
		else {
			throw std::runtime_error("no implementation available for type \"" + std::string(T::getType()) + "\" and implementation \"" + implementationName + "\" in module \"" + getName() + "\"");
		}
	}

	return *interface;
}

} /* namespace module */
} /* namespace esl */

#endif /* ESL_MODULE_MODULE_H_ */
