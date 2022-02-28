#ifndef ESL_OBJECT_CLONEABLE_H_
#define ESL_OBJECT_CLONEABLE_H_

#include <esl/object/Interface.h>

#include <memory>

namespace esl {
namespace object {

class Cloneable : public virtual Interface::Object {
public:
	virtual std::unique_ptr<Interface::Object> clone() const = 0;
};

} /* namespace object */
} /* namespace esl */

#endif /* ESL_OBJECT_CLONEABLE_H_ */
