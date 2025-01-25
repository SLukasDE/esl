#ifndef ESL_MONITORING_LOGGINGFACTORY_H_
#define ESL_MONITORING_LOGGINGFACTORY_H_

#include <esl/object/Object.h>

#include <memory>

namespace esl {
inline namespace v1_6 {
namespace monitoring {

class Logging;

class LoggingFactory : public object::Object {
public:
    virtual std::unique_ptr<Logging> createLogging() = 0;
};

} /* namespace monitoring */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_MONITORING_LOGGINGFACTORY_H_ */
