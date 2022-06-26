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

#ifndef ESL_OBJECT_PLUGINOBJECT_H_
#define ESL_OBJECT_PLUGINOBJECT_H_

#if 1

#include <esl/plugin/Plugin.h>
#include <esl/object/IObject.h>

namespace esl {
namespace object {

using PluginObject = plugin::Plugin<IObject, "esl/object/IObject">;

} /* namespace object */
} /* namespace esl */

#else

#include <esl/plugin/Plugin.h>
#include <esl/plugin/Registry.h>
#include <esl/object/IObject.h>

#include <string>
#include <vector>
#include <utility>
#include <memory>

namespace esl {
namespace object {

struct PluginObject : plugin::Plugin {
	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	using Create = std::unique_ptr<IObject>(*)(const std::vector<std::pair<std::string, std::string>>&);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */
	static inline const char* getType() {
		return "esl/object/IObject";
	}

	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	static std::unique_ptr<const plugin::Plugin> createPlugin(const char* implementation, Create create) {
		return std::unique_ptr<const plugin::Plugin>(new PluginObject(implementation, create));
	}

	PluginObject(const char* implementation, Create aCreate)
	: plugin::Plugin(getType(), implementation),
	  create(aCreate)
	{ }

	Create create;
};

} /* namespace object */
} /* namespace esl */
#endif

#endif /* ESL_OBJECT_PLUGINOBJECT_H_ */
