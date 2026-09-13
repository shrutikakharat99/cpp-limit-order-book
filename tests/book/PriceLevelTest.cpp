#include <gtest/gtest.h>

#include "book/PriceLevel.hpp"

namespace lob
{

    TEST(PriceLevelTest, StoresPrice)
    {
        PriceLevel level{ Price{100} };

        EXPECT_EQ(level.price(), Price{ 100 });
        EXPECT_TRUE(level.empty());
        EXPECT_EQ(level.size(), 0);
    }


    TEST(PriceLevelTest, AddsOrder)
    {
        PriceLevel level{ Price{100} };

        Order order{
            OrderId{1},
            Side::Buy,
            OrderType::Limit,
            Price{100},
            Quantity{100},
            TimeInForce::Day
        };

        level.addOrder(order);

        EXPECT_FALSE(level.empty());
        EXPECT_EQ(level.size(), 1);
        EXPECT_EQ(level.front().id(), OrderId{ 1 });
    }


    TEST(PriceLevelTest, MaintainsFIFOOrder)
    {
        PriceLevel level{ Price{100} };

        Order first{
            OrderId{1},
            Side::Buy,
            OrderType::Limit,
            Price{100},
            Quantity{100},
            TimeInForce::Day
        };

        Order second{
            OrderId{2},
            Side::Buy,
            OrderType::Limit,
            Price{100},
            Quantity{200},
            TimeInForce::Day
        };

        Order third{
            OrderId{3},
            Side::Buy,
            OrderType::Limit,
            Price{100},
            Quantity{300},
            TimeInForce::Day
        };

        level.addOrder(first);
        level.addOrder(second);
        level.addOrder(third);

        EXPECT_EQ(level.front().id(), OrderId{ 1 });

        level.removeFront();

        EXPECT_EQ(level.front().id(), OrderId{ 2 });

        level.removeFront();

        EXPECT_EQ(level.front().id(), OrderId{ 3 });
    }


    TEST(PriceLevelTest, RemovingFrontUpdatesSize)
    {
        PriceLevel level{ Price{100} };

        Order first{
            OrderId{1},
            Side::Buy,
            OrderType::Limit,
            Price{100},
            Quantity{100},
            TimeInForce::Day
        };

        Order second{
            OrderId{2},
            Side::Buy,
            OrderType::Limit,
            Price{100},
            Quantity{200},
            TimeInForce::Day
        };

        level.addOrder(first);
        level.addOrder(second);

        EXPECT_EQ(level.size(), 2);

        level.removeFront();

        EXPECT_EQ(level.size(), 1);
        EXPECT_EQ(level.front().id(), OrderId{ 2 });
    }


    TEST(PriceLevelTest, CannotAccessFrontWhenEmpty)
    {
        PriceLevel level{ Price{100} };

        EXPECT_THROW(
            level.front(),
            std::out_of_range
        );
    }


    TEST(PriceLevelTest, CannotRemoveFromEmptyLevel)
    {
        PriceLevel level{ Price{100} };

        EXPECT_THROW(
            level.removeFront(),
            std::out_of_range
        );
    }

} // namespace lob