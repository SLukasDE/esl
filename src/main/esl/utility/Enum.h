#ifndef ESL_UTILITY_ENUM_H_
#define ESL_UTILITY_ENUM_H_

#include <esa/utility/Enum.h>

namespace esl {
inline namespace v1_6 {
namespace utility {

template<typename EnumType, EnumType defaultType>
using Enum = esa::utility::Enum<EnumType, defaultType>;

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_UTILITY_ENUM_H_ */
