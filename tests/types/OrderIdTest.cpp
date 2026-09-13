#include <gtest/gtest.h>

#include "types/OrderId.hpp"

namespace lob
{

    TEST(OrderIdTest, StoresValue)
    {
        OrderId id{ 12345 };

        EXPECT_EQ(id.value(), 12345);
    }

    TEST(OrderIdTest, EqualIdsAreEqual)
    {
        OrderId first{ 100 };
        OrderId second{ 100 };

        EXPECT_EQ(first, second);
    }

    TEST(OrderIdTest, LowerIdIsLessThanHigherId)
    {
        OrderId lower{ 100 };
        OrderId higher{ 200 };

        EXPECT_LT(lower, higher);
    }

} // namespace lob