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

#ifndef ESL_BOOTSTRAP_MODULE_H_
#define ESL_BOOTSTRAP_MODULE_H_

#include <esl/bootstrap/Interface.h>
#include <string>

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
namespace bootstrap {

struct Module {
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

		module.interfacesProvided.id = module.id;
		module.interfacesProvided.apiVersion = module.apiVersion;
		module.interfacesProvided.next = nullptr;
	}

	const Interface& getInterfacesProvided() const;
	const Interface* getInterface(const std::string& id, const std::string& apiVersion) const;

protected:
	esl::bootstrap::Interface interfacesProvided;
	Interface* interfacesRequired = nullptr;

private:
	std::string id;
	std::string name;
	std::string variant;
	std::string version;
	std::string apiVersion;
	std::string architecture;
	std::string license;
};

} /* namespace bootstrap */
} /* namespace esl */

#endif /* ESL_BOOTSTRAP_MODULE_H_ */
