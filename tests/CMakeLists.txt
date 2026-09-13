add_executable(lob_tests
    types/PriceTest.cpp
    types/QuantityTest.cpp 
    types/OrderIdTest.cpp 
    types/EnumTest.cpp 
    model/OrderTest.cpp 
    book/PriceLevelTest.cpp 
    book/OrderBookTest.cpp)

target_link_libraries(lob_tests
    PRIVATE
        lob
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(lob_tests)