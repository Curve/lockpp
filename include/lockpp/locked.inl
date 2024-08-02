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
    [[nodiscard]] T &locked<T, Lock>::value() const &
    {
        return *m_value;
    }

    template <typename T, class Lock>
    [[nodiscard]] T &locked<T, Lock>::operator*() const &
    {
        return value();
    }

    template <typename T, class Lock>
    [[nodiscard]] T *locked<T, Lock>::operator->() const &
    {
        return m_value;
    }
} // namespace lockpp
