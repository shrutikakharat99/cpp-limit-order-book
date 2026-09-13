add_library(lob
    types/Price.cpp
    model/Order.cpp
    book/PriceLevel.cpp 
    book/OrderBook.cpp)

target_include_directories(lob
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)