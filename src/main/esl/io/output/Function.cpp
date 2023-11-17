#include <esl/io/output/Function.h>

#include <cstring>

namespace esl {
inline namespace v1_6 {
namespace io {
namespace output {

constexpr std::size_t Function::prefetchSize;

esl::io::Output Function::create(std::function<std::size_t(void*, std::size_t)> getDataFunction) {
	return esl::io::Output(std::unique_ptr<Reader>(new Function(getDataFunction)));
}

Function::Function(std::function<std::size_t(void*, std::size_t)> aGetDataFunction)
: getDataFunction(aGetDataFunction)
{ }

std::size_t Function::read(void* buffer, std::size_t count) {
	std::size_t remainingSize = data.size() - dataPos;

	if(remainingSize == 0 && getDataFunction) {
		std::size_t fetchedSize = getDataFunction(buffer, count);
		if(fetchedSize != Reader::npos) {
			fetchedDirectSize += fetchedSize;
			return fetchedSize;
		}
		getDataFunction = nullptr;
	}

	if(getDataFunction == nullptr) {
		return Reader::npos;
	}

	if(count > remainingSize) {
		count = remainingSize;
	}
	std::memcpy(buffer, &data.data()[dataPos], count);
	dataPos += count;

	return count;
}

std::size_t Function::getSizeReadable() const {
	std::size_t remainingSize = data.size() - dataPos;

	if(remainingSize == 0 && getDataFunction) {
		return Reader::npos;
	}

	return remainingSize;
}

bool Function::hasSize() const {
	/* as long getDataFunction is not nullptr, there
	 * are more data to fetch and a final size is
	 * currently not available */
	return !(getDataFunction);
}

std::size_t Function::getSize() const {
	if(!getDataFunction) {
		return data.size();
	}

	while(prefetchData() > 0) { }
	return data.size() + fetchedDirectSize;
}

std::size_t Function::prefetchData() const {
	char buffer[prefetchSize];

	if(getDataFunction) {
		std::size_t fetchedSize = getDataFunction(buffer, prefetchSize);

		if(fetchedSize != Reader::npos) {
			data.append(buffer, fetchedSize);
			return fetchedSize;
		}

		getDataFunction = nullptr;
	}

	return 0;
}

} /* namespace output */
} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */
