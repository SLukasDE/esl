#include <esl/utility/RefProcedure.h>

namespace esl {
inline namespace v1_6 {
namespace utility {

RefProcedure::RefProcedure(Procedure& aRefProcedure)
: refProcedure(aRefProcedure)
{ }

void RefProcedure::procedureRun(object::Context& context) {
	refProcedure.procedureRun(context);
}

void RefProcedure::procedureCancel() {
	refProcedure.procedureCancel();
}

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */
