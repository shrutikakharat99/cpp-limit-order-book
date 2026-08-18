#include "types/Price.hpp"

namespace lob {
	Price::Price(std::int64_t ticks) noexcept : ticks_(ticks) {}

	std::int64_t Price::value() const noexcept {
		return ticks_;
	}
}