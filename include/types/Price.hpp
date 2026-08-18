#pragma once
#include <cstdint>

namespace lob {
	class Price {
	public:
		explicit Price(std::int64_t ticks) noexcept; 

		[[nodiscard]]
		std::int64_t value() const noexcept;

		[[nodiscard]]
		bool operator==(const Price& other) const noexcept = default;

		[[nodiscard]]
		bool operator<=>(const Price& other) const noexcept = default;
	private:
		int64_t ticks_;
	};
}