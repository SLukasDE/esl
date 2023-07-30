#ifndef ESL_EXAMPLES_LOGGING_EXAMPLE04_H_
#define ESL_EXAMPLES_LOGGING_EXAMPLE04_H_

#include <esl/examples/Logger.h>

namespace esl {
inline namespace v1_6 {
namespace examples {
namespace logging {

class Example04 {
public:
	Example04() = default;
	~Example04() = default;

	float divide(float a, float b);
};

void example04();

} /* namespace logging */
} /* namespace examples */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_EXAMPLES_LOGGING_EXAMPLE04_H_ */
