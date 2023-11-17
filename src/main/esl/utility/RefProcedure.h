#ifndef ESL_UTILITY_REFPROCEDURE_H_
#define ESL_UTILITY_REFPROCEDURE_H_

#include <esl/object/Context.h>
#include <esl/object/Procedure.h>

namespace esl {
inline namespace v1_6 {
namespace utility {

class RefProcedure final : public object::Procedure {
public:
	RefProcedure(Procedure& aRefProcedure);

	void procedureRun(object::Context& context) override;
	void procedureCancel() override;

private:
	Procedure& refProcedure;
};

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_UTILITY_REFPROCEDURE_H_ */
