#include <cstddef>
#include <deque>
#include <functional>
#include "types/Price.hpp"
#include "model/Order.hpp"

namespace lob {
	class PriceLevel {
	public:
		explicit PriceLevel(Price price)noexcept;
		Price price() const noexcept;
		void addOrder(Order& order);
		Order& front();
		const Order& front() const;
		void removeFront();
		bool empty() const noexcept;
		std::size_t size() const noexcept;

	private:
		Price price_;
		std::deque<std::reference_wrapper<Order>> orders_;
	};
}