#ifndef ESL_OBJECT_VALUE_H_
#define ESL_OBJECT_VALUE_H_

#include <esl/object/Interface.h>
#include <esl/object/Cloneable.h>

#include <memory>

namespace esl {
namespace object {

template <typename T>
class Value : public Cloneable {
public:
	Value(const T& aValue)
	: value(aValue)
	{ }

	Value(T&& aValue)
	: value(std::move(aValue))
	{ }

	std::unique_ptr<esl::object::Interface::Object> clone() const override {
		return std::unique_ptr<esl::object::Interface::Object>(new Value<T>(value));
	}

	T& operator=(const T& aValue) {
		value = aValue;
		return value;
	}

	T& operator=(T&& aValue) {
		value = std::move(aValue);
		return value;
	}

	const T& operator*() const noexcept {
		return value;
	}

	T& operator*() noexcept {
		return value;
	}

	const T& operator->() const noexcept {
		return value;
	}

	T& operator->() noexcept {
		return value;
	}

	const T& get() const noexcept {
		return value;
	}

	T& get() noexcept {
		return value;
	}

private:
	T value;
};

} /* namespace object */
} /* namespace esl */

#endif /* ESL_OBJECT_VALUE_H_ */
