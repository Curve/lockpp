#pragma once
#include <cstdint>
#include <utility>

namespace sxl
{
    namespace traits
    {
        template <typename T>
        class is_read_lock
        {
            static auto test(...) -> std::uint8_t;
            template <typename O>
            static auto test(O *) -> decltype(std::declval<O>().lock_shared(), std::uint16_t{});

          public:
            static const bool value = sizeof(test(reinterpret_cast<T *>(0))) == sizeof(std::uint16_t);
        };
    } // namespace traits
} // namespace sxl
