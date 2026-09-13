#pragma once
#include <cstdint>
#include <compare>
#include <stdexcept>

namespace lob {
	class Quantity {
	public:
		explicit constexpr Quantity(std::uint64_t value) noexcept :value_(value) {}
		
		[[nodiscard]]
		constexpr std::uint64_t value() const noexcept {
			return value_;
		}
		
		[[nodiscard]]
		constexpr Quantity operator+(const Quantity& other) const noexcept {
			return Quantity(value_ + other.value_);
		}
		
		[[nodiscard]]
		constexpr Quantity operator-(const Quantity& other) const {
			if (other.value_ > value_) {
				throw std::underflow_error("Quantity subtraction would result in negative quantity");
			}
			return Quantity(value_ - other.value_);
		}

		[[nodiscard]]
		constexpr bool operator==(const Quantity& other) const noexcept = default;
		
		[[nodiscard]]
		constexpr std::strong_ordering operator<=>(const Quantity& other) const noexcept = default;

	private:
		std::uint64_t value_;
	};
}