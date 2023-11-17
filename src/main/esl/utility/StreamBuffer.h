#ifndef ESL_UTILITY_STREAMBUFFER_H_
#define ESL_UTILITY_STREAMBUFFER_H_

#include <functional>
#include <streambuf>
#include <vector>

namespace esl {
inline namespace v1_6 {
namespace utility {

class StreamBuffer : public std::streambuf {
public:
    StreamBuffer(std::size_t bufferSize, std::function<void(const char*, std::size_t)> writeHandler);

private:
    int_type overflow(int_type ch) override;
    int sync() override;

    std::size_t bufferSize;
    std::vector<char> buffer;
    std::function<void(const char*, std::size_t)> writeHandler;
};

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_UTILITY_STREAMBUFFER_H_ */
