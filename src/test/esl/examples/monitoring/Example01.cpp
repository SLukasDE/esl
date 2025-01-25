#include <esl/examples/monitoring/Example01.h>
#include <esl/monitoring/Logger.h>

namespace esl {
inline namespace v1_6 {
namespace examples {
namespace monitoring {

void example01() {
	/* creating a logger class */
	//esl::monitoring::Logger<esl::monitoring::Streams::Level::INFO> logger;

	/* That's it, now you can use it already */
	//logger.info << "Hello world!" << std::endl;

	/* Ups, you see nothing.
	 * We have not "initialized" the logging framework.
	 * Let's go to logger example 2 to see how to initialize... */
}

} /* namespace monitoring */
} /* namespace examples */
} /* inline namespace v1_6 */
} /* namespace esl */
