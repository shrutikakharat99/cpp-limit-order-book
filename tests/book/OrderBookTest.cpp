#include <gtest/gtest.h>

#include "book/OrderBook.hpp"

namespace lob
{

    TEST(OrderBookTest, AddAndFindBuyOrder)
    {
        OrderBook book;

        Order order{
            OrderId{1},
            Side::Buy,
            OrderType::Limit,
            Price{100},
            Quantity{100},
            TimeInForce::Day
        };

        book.addOrder(order);

        EXPECT_TRUE(book.contains(OrderId{ 1 }));

        Order* storedOrder = book.findOrder(OrderId{ 1 });

        ASSERT_NE(storedOrder, nullptr);
        EXPECT_EQ(storedOrder->id(), OrderId{ 1 });
        EXPECT_EQ(storedOrder->side(), Side::Buy);
        EXPECT_EQ(storedOrder->price(), Price{ 100 });
        EXPECT_EQ(storedOrder->quantity(), Quantity{ 100 });
    }
    TEST(OrderBookTest, AddAndFindSellOrder)
    {
        OrderBook book;

        Order order{
            OrderId{2},
            Side::Sell,
            OrderType::Limit,
            Price{103},
            Quantity{50},
            TimeInForce::Day
        };

        book.addOrder(order);

        EXPECT_TRUE(book.contains(OrderId{ 2 }));

        Order* storedOrder = book.findOrder(OrderId{ 2 });

        ASSERT_NE(storedOrder, nullptr);

        EXPECT_EQ(storedOrder->id(), OrderId{ 2 });
        EXPECT_EQ(storedOrder->side(), Side::Sell);
        EXPECT_EQ(storedOrder->price(), Price{ 103 });
        EXPECT_EQ(storedOrder->quantity(), Quantity{ 50 });
    }
    TEST(OrderBookTest, FindNonExistingOrderReturnsNull)
    {
        OrderBook book;

        EXPECT_FALSE(book.contains(OrderId{ 999 }));
        EXPECT_EQ(book.findOrder(OrderId{ 999 }), nullptr);
    }
    TEST(OrderBookTest, StoresMultipleOrders)
    {
        OrderBook book;

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
            Price{101},
            Quantity{200},
            TimeInForce::Day
        };

        Order third{
            OrderId{3},
            Side::Sell,
            OrderType::Limit,
            Price{103},
            Quantity{50},
            TimeInForce::Day
        };

        book.addOrder(first);
        book.addOrder(second);
        book.addOrder(third);

        EXPECT_TRUE(book.contains(OrderId{ 1 }));
        EXPECT_TRUE(book.contains(OrderId{ 2 }));
        EXPECT_TRUE(book.contains(OrderId{ 3 }));
    }
    TEST(OrderBookTest, PriceLevelReferencesStoredOrder)
    {
        OrderBook book;

        Order order{
            OrderId{1},
            Side::Buy,
            OrderType::Limit,
            Price{100},
            Quantity{100},
            TimeInForce::Day
        };

        book.addOrder(order);

        Order* storedOrder = book.findOrder(OrderId{ 1 });

        ASSERT_NE(storedOrder, nullptr);

        storedOrder->fill(Quantity{ 40 });

        EXPECT_EQ(
            storedOrder->remainingQuantity(),
            Quantity{ 60 }
        );
    }
    TEST(OrderBookTest, EmptyBookHasNoBestBidOrAsk)
    {
        OrderBook book;

        EXPECT_FALSE(book.bestBid().has_value());
        EXPECT_FALSE(book.bestAsk().has_value());
    }
    TEST(OrderBookTest, BestBidIsHighestBuyPrice)
    {
        OrderBook book;

        book.addOrder(Order{
            OrderId{1},
            Side::Buy,
            OrderType::Limit,
            Price{100},
            Quantity{100},
            TimeInForce::Day
            });

        book.addOrder(Order{
            OrderId{2},
            Side::Buy,
            OrderType::Limit,
            Price{102},
            Quantity{100},
            TimeInForce::Day
            });

        book.addOrder(Order{
            OrderId{3},
            Side::Buy,
            OrderType::Limit,
            Price{101},
            Quantity{100},
            TimeInForce::Day
            });

        ASSERT_TRUE(book.bestBid().has_value());
        EXPECT_EQ(book.bestBid().value(), Price{ 102 });
    }
    TEST(OrderBookTest, BestAskIsLowestSellPrice)
    {
        OrderBook book;

        book.addOrder(Order{
            OrderId{1},
            Side::Sell,
            OrderType::Limit,
            Price{105},
            Quantity{100},
            TimeInForce::Day
            });

        book.addOrder(Order{
            OrderId{2},
            Side::Sell,
            OrderType::Limit,
            Price{103},
            Quantity{100},
            TimeInForce::Day
            });

        book.addOrder(Order{
            OrderId{3},
            Side::Sell,
            OrderType::Limit,
            Price{104},
            Quantity{100},
            TimeInForce::Day
            });

        ASSERT_TRUE(book.bestAsk().has_value());
        EXPECT_EQ(book.bestAsk().value(), Price{ 103 });
    }
}