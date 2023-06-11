#pragma once
#include "locked.hpp"

namespace lockpp
{
    template <typename Type, template <typename> class Lock, typename Mutex>
    template <typename... LockArgs>
    locked<Type, Lock, Mutex>::locked(Type &value, Mutex &mutex, LockArgs &&...lock_args)
        : m_lock(mutex, std::forward<LockArgs>(lock_args)...), m_value(value)
    {
    }

    template <typename Type, template <typename> class Lock, typename Mutex>
    [[nodiscard]] Type &locked<Type, Lock, Mutex>::operator*() noexcept
    {
        return m_value;
    }

    template <typename Type, template <typename> class Lock, typename Mutex>
    [[nodiscard]] Type &locked<Type, Lock, Mutex>::operator*() const noexcept
    {
        return m_value;
    }

    template <typename Type, template <typename> class Lock, typename Mutex>
    [[nodiscard]] Type *locked<Type, Lock, Mutex>::operator->() noexcept
    {
        return &m_value;
    }

    template <typename Type, template <typename> class Lock, typename Mutex>
    [[nodiscard]] Type *locked<Type, Lock, Mutex>::operator->() const noexcept
    {
        return &m_value;
    }
} // namespace lockpp