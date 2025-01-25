#ifndef ESL_PLUGIN_EXCEPTION_PLUGINNOTFOUND_H_
#define ESL_PLUGIN_EXCEPTION_PLUGINNOTFOUND_H_

#include <stdexcept>
#include <string>
#include <typeindex>

namespace esl {
inline namespace v1_6 {
namespace plugin {
namespace exception {

class PluginNotFound : public std::runtime_error {
public:
	PluginNotFound(std::type_index typeIndex);
	PluginNotFound(std::type_index typeIndex, const std::string& implementation);
	PluginNotFound(std::type_index typeIndex, const std::string& implementation, const char* message);
	PluginNotFound(std::type_index typeIndex, const std::string& implementation, const std::string& message);

	const std::string& getImplementation() const noexcept;
	std::type_index getTypeIndex() const noexcept;

private:
	const std::type_index typeIndex;
	const std::string implementation;
};

} /* namespace exception */
} /* namespace plugin */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_PLUGIN_EXCEPTION_PLUGINNOTFOUND_H_ */
