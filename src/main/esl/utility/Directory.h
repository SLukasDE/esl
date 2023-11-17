#ifndef ESL_UTILITY_DIRECTORY_H_
#define ESL_UTILITY_DIRECTORY_H_

#include <esl/utility/Time.h>

#include <string>
#include <vector>

namespace esl {
inline namespace v1_6 {
namespace utility {

class Directory {
public:
	struct Entry {
	    std::string name;
	    std::string path;
	    std::size_t size = 0;

	    Time ts;
	    bool isExecutable = false;
	    bool isDirectory = false;
	};

	Directory(std::string path);

    Entry getEntry() const;
    std::vector<Entry> scan(bool recursive = true) const;

private:
    std::string path;
};

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_UTILITY_DIRECTORY_H_ */
