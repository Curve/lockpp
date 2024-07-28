#pragma once

#include <type_traits>

namespace lockpp
{
    template <typename T, typename Lock>
    class locked
    {
        template <typename, typename>
        friend class lock;

      private:
        Lock m_lock;
        T *m_value;

      protected:
        template <typename Mutex, typename... Ts>
        locked(T *, Mutex &, Ts &&...);

      public:
        template <typename Self>
            requires std::is_lvalue_reference_v<Self>
        [[nodiscard]] T &value(this Self &&) noexcept;

      public:
        template <typename Self>
            requires std::is_lvalue_reference_v<Self>
        [[nodiscard]] T &operator*(this Self &&) noexcept;

        template <typename Self>
            requires std::is_lvalue_reference_v<Self>
        [[nodiscard]] T *operator->(this Self &&) noexcept;
    };
} // namespace lockpp

#include "locked.inl"
