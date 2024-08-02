#pragma once

#include "lock.hpp"

namespace lockpp
{
    template <typename T, typename Mutex>
    template <typename... Ts>
    lock<T, Mutex>::lock(Ts &&...args) : m_value(std::forward<Ts>(args)...)
    {
    }

    template <typename T, typename Mutex>
    template <template <typename> class Lock, typename... Ts>
    locked<T, Lock<Mutex>> lock<T, Mutex>::write(Ts &&...lock_args) &
    {
        return {&m_value, m_mutex, std::forward<Ts>(lock_args)...};
    }

    template <typename T, typename Mutex>
    template <template <typename> class Lock, typename... Ts>
    locked<const T, Lock<Mutex>> lock<T, Mutex>::read(Ts &&...lock_args) const &
    {
        return {&m_value, m_mutex, std::forward<Ts>(lock_args)...};
    }

    template <typename T, typename Mutex>
    template <typename O>
        requires std::assignable_from<T &, O>
    void lock<T, Mutex>::assign(O &&value) &
    {
        auto locked = write();
        *locked     = std::forward<O>(value);
    }

    template <typename T, typename Mutex>
    T &lock<T, Mutex>::get_unsafe() &
    {
        return m_value;
    }

    template <typename T, typename Mutex>
    T &lock<T, Mutex>::get_unsafe() const &
    {
        return m_value;
    }

    template <typename T, typename Mutex>
    T lock<T, Mutex>::copy() const &
    {
        auto locked = read();
        return *locked;
    }
} // namespace lockpp
