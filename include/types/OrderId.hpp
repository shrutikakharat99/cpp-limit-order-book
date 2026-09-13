#pragma once

#include <cstdint>
#include <compare>

namespace lob
{

    class OrderId
    {
    public:
        explicit OrderId(std::uint64_t value) noexcept
            : value_(value)
        {
        }

        [[nodiscard]]
        std::uint64_t value() const noexcept
        {
            return value_;
        }

        [[nodiscard]]
        bool operator==(const OrderId& other) const noexcept = default;

        [[nodiscard]]
        auto operator<=>(const OrderId& other) const noexcept = default;

    private:
        std::uint64_t value_;
    };

} // namespace lob

namespace std
{

    template<>
    struct hash<lob::OrderId>
    {
        std::size_t operator()(const lob::OrderId& id) const noexcept
        {
            return std::hash<std::uint64_t>{}(id.value());
        }
    };

} // namespace std