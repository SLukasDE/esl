#ifndef ESL_OBJECT_CLONEABLE_H_
#define ESL_OBJECT_CLONEABLE_H_

#include <esl/object/Object.h>

#include <memory>

namespace esl {
inline namespace v1_6 {
namespace object {

class Cloneable : public virtual Object {
public:
	virtual std::unique_ptr<Object> clone() const = 0;
};

} /* namespace object */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_OBJECT_CLONEABLE_H_ */
