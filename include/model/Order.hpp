#pragma once

#include <optional>
#include "types/Price.hpp"
#include "types/Side.hpp"
#include "types/OrderTypes.hpp"
#include "types/OrderId.hpp"
#include "types/TimeInForce.hpp"
#include "types/Quantity.hpp"

namespace lob
{

    class Order
    {
    public:
        Order(
            OrderId id,
            Side side,
            OrderType type,
            std::optional<Price> price,
            Quantity quantity,
            TimeInForce timeInForce
        ) noexcept;

        [[nodiscard]]
        OrderId id() const noexcept;

        [[nodiscard]]
        Side side() const noexcept;

        [[nodiscard]]
        OrderType type() const noexcept;

        [[nodiscard]]
        const std::optional<Price>& price() const noexcept;

        [[nodiscard]]
        Quantity quantity() const noexcept;

        [[nodiscard]]
        Quantity remainingQuantity() const noexcept;

        [[nodiscard]]
        TimeInForce timeInForce() const noexcept;

        void fill(Quantity quantity);

    private:
        OrderId id_;
        Side side_;
        OrderType type_;
        std::optional<Price> price_;
        Quantity quantity_;
        Quantity remainingQuantity_;
        TimeInForce timeInForce_;
    };

} // namespace lob