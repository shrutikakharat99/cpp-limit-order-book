add_library(lob
    types/Price.cpp
)

target_include_directories(lob
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)