#include <gtest/gtest.h>

#include "types/Side.hpp"
#include "types/OrderTypes.hpp"
#include "types/TimeInForce.hpp"

namespace lob
{

    TEST(SideTest, HasBuyAndSellValues)
    {
        EXPECT_NE(Side::Buy, Side::Sell);
    }

    TEST(OrderTypeTest, HasMarketAndLimitValues)
    {
        EXPECT_NE(OrderType::Market, OrderType::Limit);
    }

    TEST(TimeInForceTest, HasExpectedValues)
    {
        EXPECT_NE(TimeInForce::Day, TimeInForce::IOC);
        EXPECT_NE(TimeInForce::IOC, TimeInForce::FOK);
        EXPECT_NE(TimeInForce::FOK, TimeInForce::GTC);
    }

} // namespace lob