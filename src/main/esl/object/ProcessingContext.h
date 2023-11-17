#ifndef ESL_OBJECT_PROCESSINGCONTEXT_H_
#define ESL_OBJECT_PROCESSINGCONTEXT_H_

#include <esl/object/Context.h>

#include <esa/object/ProcessingContext.h>

namespace esl {
inline namespace v1_6 {
namespace object {

class ProcessingContext : public esa::object::ProcessingContext {
public:
	void run(Context& objectContext, int argc, const char *argv[]);
	void run();
	void run(int argc, const char *argv[]);

	int main(Context& objectContext);
	int main(Context& objectContext, int argc, const char *argv[]);
	int main();
	int main(int argc, const char *argv[]);
};

} /* namespace object */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_OBJECT_PROCESSINGCONTEXT_H_ */
