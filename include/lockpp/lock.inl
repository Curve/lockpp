#pragma once

#include "lock.hpp"
#include "locked.hpp"

namespace lockpp
{
    namespace
    {
        template <typename T>
        decltype(auto) unwrap(T &value)
        {
            if constexpr (requires(T &value) {
                              { *value };
                          })
            {
                return *value;
            }
            else
            {
                return value;
            }
        }
    } // namespace

    template <typename T, typename Mutex>
    template <typename... Ts>
        requires std::constructible_from<T, Ts...>
    lock<T, Mutex>::lock(Ts &&...args) : m_value(std::forward<Ts>(args)...)
    {
    }

    template <typename T, typename Mutex>
    template <template <typename> class Lock, typename... Ts>
    auto lock<T, Mutex>::write(Ts &&...lock_args) &
    {
        return locked<T, Lock<mutex>>{std::addressof(m_value), unwrap(m_mutex), std::forward<Ts>(lock_args)...};
    }

    template <typename T, typename Mutex>
    template <template <typename> class Lock, typename Self, typename... Ts>
        requires std::is_lvalue_reference_v<Self>
    auto lock<T, Mutex>::read(this Self &&self, Ts &&...lock_args)
    {
        return locked<const T, Lock<mutex>>{std::addressof(std::forward<Self>(self).m_value),
                                            unwrap(std::forward<Self>(self).m_mutex), std::forward<Ts>(lock_args)...};
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
    template <typename Self>
        requires std::is_lvalue_reference_v<Self>
    T &lock<T, Mutex>::get_unsafe(this Self &&self)
    {
        return std::forward<Self>(self).m_value;
    }

    template <typename T, typename Mutex>
    template <typename Self>
        requires std::is_lvalue_reference_v<Self> and std::copyable<T>
    T lock<T, Mutex>::copy(this Self &&self)
    {
        auto locked = std::forward<Self>(self).read();
        return *locked;
    }
} // namespace lockpp
