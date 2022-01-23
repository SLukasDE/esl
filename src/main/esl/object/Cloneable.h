#ifndef ESL_OBJECT_CLONEABLE_H_
#define ESL_OBJECT_CLONEABLE_H_

#include <esl/object/Interface.h>

#include <memory>

namespace esl {
namespace object {

class Cloneable : public esl::object::Interface::Object {
public:
	virtual std::unique_ptr<esl::object::Interface::Object> clone() const = 0;
};

} /* namespace object */
} /* namespace esl */

#endif /* ESL_OBJECT_CLONEABLE_H_ */
