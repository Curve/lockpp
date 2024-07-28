#pragma once

#include "locked.hpp"
#include <utility>

namespace lockpp
{
    template <typename T, class Lock>
    template <typename Mutex, typename... Ts>
    locked<T, Lock>::locked(T *value, Mutex &mutex, Ts &&...lock_args)
        : m_lock(mutex, std::forward<Ts>(lock_args)...), m_value(value)
    {
    }

    template <typename T, class Lock>
    template <typename Self>
        requires std::is_lvalue_reference_v<Self>
    [[nodiscard]] T &locked<T, Lock>::value(this Self &&self) noexcept
    {
        return *self.m_value;
    }

    template <typename T, class Lock>
    template <typename Self>
        requires std::is_lvalue_reference_v<Self>
    [[nodiscard]] T &locked<T, Lock>::operator*(this Self &&self) noexcept
    {
        return self.value();
    }

    template <typename T, class Lock>
    template <typename Self>
        requires std::is_lvalue_reference_v<Self>
    [[nodiscard]] T *locked<T, Lock>::operator->(this Self &&self) noexcept
    {
        return self.m_value;
    }
} // namespace lockpp
