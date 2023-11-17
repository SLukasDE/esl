#include <esl/io/output/String.h>
#include <esl/Logger.h>

#include <esl/monitoring/Streams.h>

namespace esl {
inline namespace v1_6 {
namespace io {
namespace output {

namespace {
Logger logger("esl::io::output::String");
}

esl::io::Output String::create(std::string content) {
	return esl::io::Output(std::unique_ptr<Producer>(new String(std::move(content))));
}

String::String(std::string aContent)
: str(std::move(aContent)),
  data(str.data()),
  size(str.size() == 0 ? esl::io::Writer::npos : str.size())
{ }

std::size_t String::produce(esl::io::Writer& writer) {
	if(currentPos >= size) {
		size = esl::io::Writer::npos;
		return esl::io::Writer::npos;
	}

	if(size == esl::io::Writer::npos) {
		return esl::io::Writer::npos;
	}

	std::size_t count = writer.write(&data[currentPos], size - currentPos);
	if(count == esl::io::Writer::npos) {
		currentPos = size;
	}
	else {
		if(currentPos + count > size) {
			logger.warn << "output::String has been called with a broken writer!\n";
			logger.warn << "Writer read " << count << " bytes but at most " << (size - currentPos) << " bytes was allowed to read.\n";
			count = size - currentPos;
		}
		currentPos += count;
	}

	return count;
}

} /* namespace output */
} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */
