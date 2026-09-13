#include <gtest/gtest.h>
#include <types/Price.hpp>

namespace lob {
	TEST(PriceTest, StoreValue) {
		Price price{ 10025 };
		EXPECT_EQ(price.value(), 10025);
	}
	TEST(PriceTest, EqualPricesAreEqual)
	{
		Price first{ 100 };
		Price second{ 100 };

		EXPECT_EQ(first, second);
	}
	TEST(PriceTest, LowerPriceIsLessThanHigherPrice)
	{
		Price lower{ 100 };
		Price higher{ 101 };

		EXPECT_LT(lower, higher);
	}
}