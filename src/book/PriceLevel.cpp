#include "book/PriceLevel.hpp"
#include <stdexcept>

namespace lob {
	PriceLevel::PriceLevel(Price price) noexcept :price_(price) {
	}

	Price PriceLevel::price() const noexcept {
		return price_;
	}

	void PriceLevel::addOrder(Order& order) {
		orders_.push_back(order);
	}

	Order& PriceLevel::front() {
		if (orders_.empty()) {
			throw std::out_of_range("Orders are empty!");
		}
		return orders_.front().get();
	}

	const Order& PriceLevel::front() const
	{
		if (orders_.empty())
		{
			throw std::out_of_range("PriceLevel is empty");
		}

		return orders_.front().get();
	}

	void PriceLevel::removeFront()
	{
		if (orders_.empty())
		{
			throw std::out_of_range("Cannot remove from an empty PriceLevel");
		}

		orders_.pop_front();
	}

	bool PriceLevel::empty() const noexcept
	{
		return orders_.empty();
	}

	std::size_t PriceLevel::size() const noexcept
	{
		return orders_.size();
	}

}