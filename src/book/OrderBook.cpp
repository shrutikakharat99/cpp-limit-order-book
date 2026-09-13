#include "book/OrderBook.hpp"

namespace lob
{

    void OrderBook::addOrder(Order order)
    {
        const OrderId id = order.id();

        auto [it, inserted] = orders_.emplace(id, std::move(order));

        if (!inserted)
        {
            return;
        }

        Order& storedOrder = it->second;

        if (!storedOrder.price().has_value())
        {
            return;
        }

        const Price price = storedOrder.price().value();

        if (storedOrder.side() == Side::Buy)
        {
            auto [levelIt, levelInserted] =
                bids_.try_emplace(price, PriceLevel{ price });

            levelIt->second.addOrder(storedOrder);
        }
        else
        {
            auto [levelIt, levelInserted] =
                asks_.try_emplace(price, PriceLevel{ price });

            levelIt->second.addOrder(storedOrder);
        }
    }

    bool OrderBook::contains(OrderId id) const noexcept
    {
        return orders_.contains(id);
    }

    Order* OrderBook::findOrder(OrderId id) noexcept
    {
        auto it = orders_.find(id);

        if (it == orders_.end())
        {
            return nullptr;
        }

        return &it->second;
    }

    const Order* OrderBook::findOrder(OrderId id) const noexcept
    {
        auto it = orders_.find(id);

        if (it == orders_.end())
        {
            return nullptr;
        }

        return &it->second;
    }
    std::optional<Price> OrderBook::bestBid() const noexcept
    {
        if (bids_.empty())
        {
            return std::nullopt;
        }

        return bids_.begin()->first;
    }

    std::optional<Price> OrderBook::bestAsk() const noexcept
    {
        if (asks_.empty())
        {
            return std::nullopt;
        }

        return asks_.begin()->first;
    }
} // namespace lob