#include <esl/plugin/exception/PluginNotFound.h>

namespace esl {
inline namespace v1_6 {
namespace plugin {
namespace exception {

PluginNotFound::PluginNotFound(std::type_index aTypeIndex)
: std::runtime_error("No implementation found for plugin " + std::string(aTypeIndex.name())),
  typeIndex(aTypeIndex)
{ }

PluginNotFound::PluginNotFound(std::type_index aTypeIndex, const std::string& aImplementation)
: std::runtime_error("Implementation \"" + aImplementation + "\" not found for plugin " + std::string(aTypeIndex.name())),
  typeIndex(aTypeIndex),
  implementation(aImplementation)
{ }

PluginNotFound::PluginNotFound(std::type_index aTypeIndex, const std::string& aImplementation, const char* message)
: std::runtime_error(message),
  typeIndex(aTypeIndex),
  implementation(aImplementation)
{ }

PluginNotFound::PluginNotFound(std::type_index aTypeIndex, const std::string& aImplementation, const std::string& message)
: std::runtime_error(message),
  typeIndex(aTypeIndex),
  implementation(aImplementation)
{ }

const std::string& PluginNotFound::getImplementation() const noexcept {
	return implementation;
}

std::type_index PluginNotFound::getTypeIndex() const noexcept {
	return typeIndex;
}

} /* namespace exception */
} /* namespace plugin */
} /* inline namespace v1_6 */
} /* namespace esl */
