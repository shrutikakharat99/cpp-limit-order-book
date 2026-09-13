#include <gtest/gtest.h>
#include <stdexcept>
#include "types/Quantity.hpp"

namespace lob
{

    TEST(QuantityTest, StoresValue)
    {
        Quantity quantity{ 100 };

        EXPECT_EQ(quantity.value(), 100);
    }

    TEST(QuantityTest, AddsQuantities)
    {
        Quantity first{ 100 };
        Quantity second{ 50 };

        Quantity result = first + second;

        EXPECT_EQ(result.value(), 150);
    }

    TEST(QuantityTest, SubtractsQuantities)
    {
        Quantity first{ 100 };
        Quantity second{ 40 };

        Quantity result = first - second;

        EXPECT_EQ(result.value(), 60);
    }

    TEST(QuantityTest, EqualQuantitiesAreEqual)
    {
        Quantity first{ 100 };
        Quantity second{ 100 };

        EXPECT_EQ(first, second);
    }

    TEST(QuantityTest, LowerQuantityIsLessThanHigherQuantity)
    {
        Quantity lower{ 50 };
        Quantity higher{ 100 };

        EXPECT_LT(lower, higher);
    }

    TEST(QuantityTest, CannotSubtractLargerQuantity)
    {
        Quantity smaller{ 50 };
        Quantity larger{ 100 };

        EXPECT_THROW(
            smaller - larger,
            std::underflow_error
        );
    }

} // namespace lob