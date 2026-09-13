#pragma once

#include <functional>
#include <map>
#include <unordered_map>
#include <optional>
#include "book/PriceLevel.hpp"
#include "model/Order.hpp"

namespace lob
{

    class OrderBook
    {
    public:
        void addOrder(Order order);

        bool contains(OrderId id) const noexcept;

        Order* findOrder(OrderId id) noexcept;
        const Order* findOrder(OrderId id) const noexcept;

        std::optional<Price> bestBid() const noexcept;
        std::optional<Price> bestAsk() const noexcept;
    private:
        using BidLevels = std::map<Price,PriceLevel,std::greater<Price>>;

        using AskLevels = std::map<Price,PriceLevel,std::less<Price>>;

        std::unordered_map<OrderId, Order> orders_;

        BidLevels bids_;
        AskLevels asks_;
    };

} // namespace lob