#ifndef ESL_LOGGER_H_
#define ESL_LOGGER_H_

#include <esl/monitoring/Logger.h>
#include <esl/monitoring/Streams.h>

namespace esl {
inline namespace v1_6 {

#ifdef ESL_MONITORING_LEVEL_DEBUG
using Logger = monitoring::Logger<monitoring::Streams::Level::TRACE>;
#else
using Logger = monitoring::Logger<monitoring::Streams::Level::WARN>;
#endif

} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_LOGGER_H_ */
