#include "model/Order.hpp"

#include <stdexcept>

namespace lob
{

    Order::Order(
        OrderId id,
        Side side,
        OrderType type,
        std::optional<Price> price,
        Quantity quantity,
        TimeInForce timeInForce
    ) noexcept
        : id_(id),
        side_(side),
        type_(type),
        price_(price),
        quantity_(quantity),
        remainingQuantity_(quantity),
        timeInForce_(timeInForce)
    {
    }

    OrderId Order::id() const noexcept
    {
        return id_;
    }

    Side Order::side() const noexcept
    {
        return side_;
    }

    OrderType Order::type() const noexcept
    {
        return type_;
    }

    const std::optional<Price>& Order::price() const noexcept
    {
        return price_;
    }

    Quantity Order::quantity() const noexcept
    {
        return quantity_;
    }

    Quantity Order::remainingQuantity() const noexcept
    {
        return remainingQuantity_;
    }

    TimeInForce Order::timeInForce() const noexcept
    {
        return timeInForce_;
    }

    void Order::fill(Quantity quantity)
    {
        if (quantity > remainingQuantity_)
        {
            throw std::invalid_argument(
                "Fill quantity exceeds remaining order quantity"
            );
        }

        remainingQuantity_ = remainingQuantity_ - quantity;
    }

} // namespace lob