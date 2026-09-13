#include <gtest/gtest.h>

#include <stdexcept>

#include "model/Order.hpp"

namespace lob
{

    TEST(OrderTest, StoresInitialState)
    {
        Order order{
            OrderId{1},
            Side::Buy,
            OrderType::Limit,
            Price{100},
            Quantity{200},
            TimeInForce::Day
        };

        EXPECT_EQ(order.id(), OrderId{ 1 });
        EXPECT_EQ(order.side(), Side::Buy);
        EXPECT_EQ(order.type(), OrderType::Limit);
        ASSERT_TRUE(order.price().has_value());
        EXPECT_EQ(order.price().value(), Price{ 100 });

        EXPECT_EQ(order.quantity(), Quantity{ 200 });
        EXPECT_EQ(order.remainingQuantity(), Quantity{ 200 });
        EXPECT_EQ(order.timeInForce(), TimeInForce::Day);
    }
    TEST(OrderTest, FillReducesRemainingQuantity)
    {
        Order order{
            OrderId{1},
            Side::Buy,
            OrderType::Limit,
            Price{100},
            Quantity{200},
            TimeInForce::Day
        };

        order.fill(Quantity{ 50 });

        EXPECT_EQ(order.quantity(), Quantity{ 200 });
        EXPECT_EQ(order.remainingQuantity(), Quantity{ 150 });
    }
    TEST(OrderTest, CanBePartiallyFilledMultipleTimes)
    {
        Order order{
            OrderId{1},
            Side::Buy,
            OrderType::Limit,
            Price{100},
            Quantity{200},
            TimeInForce::Day
        };

        order.fill(Quantity{ 50 });
        order.fill(Quantity{ 100 });

        EXPECT_EQ(order.quantity(), Quantity{ 200 });
        EXPECT_EQ(order.remainingQuantity(), Quantity{ 50 });
    }
    TEST(OrderTest, CanBeCompletelyFilled)
    {
        Order order{
            OrderId{1},
            Side::Buy,
            OrderType::Limit,
            Price{100},
            Quantity{200},
            TimeInForce::Day
        };

        order.fill(Quantity{ 200 });

        EXPECT_EQ(order.quantity(), Quantity{ 200 });
        EXPECT_EQ(order.remainingQuantity(), Quantity{ 0 });
    }
    TEST(OrderTest, CannotOverfill)
    {
        Order order{
            OrderId{1},
            Side::Buy,
            OrderType::Limit,
            Price{100},
            Quantity{200},
            TimeInForce::Day
        };

        EXPECT_THROW(
            order.fill(Quantity{ 250 }),
            std::invalid_argument
        );

        // State must remain unchanged after the failed operation.
        EXPECT_EQ(order.remainingQuantity(), Quantity{ 200 });
    }
    TEST(OrderTest, MarketOrderHasNoPrice)
    {
        Order order{
            OrderId{2},
            Side::Sell,
            OrderType::Market,
            std::nullopt,
            Quantity{100},
            TimeInForce::IOC
        };

        EXPECT_EQ(order.type(), OrderType::Market);
        EXPECT_FALSE(order.price().has_value());
        EXPECT_EQ(order.quantity(), Quantity{ 100 });
        EXPECT_EQ(order.remainingQuantity(), Quantity{ 100 });
        EXPECT_EQ(order.timeInForce(), TimeInForce::IOC);
    }
}