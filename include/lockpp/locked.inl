#pragma once
#include "locked.hpp"

namespace lockpp
{
    template <typename Type, template <typename> class Lock, typename Mutex>
    template <typename... LockArgs>
    locked<Type, Lock, Mutex>::locked(std::add_lvalue_reference_t<Type> value, Mutex &mutex, LockArgs &&...lock_args)
        : m_lock(mutex, std::forward<LockArgs>(lock_args)...), m_value(value)
    {
    }

    template <typename Type, template <typename> class Lock, typename Mutex>
    [[nodiscard]] std::add_lvalue_reference_t<Type> locked<Type, Lock, Mutex>::operator*() noexcept
    {
        return m_value;
    }

    template <typename Type, template <typename> class Lock, typename Mutex>
    [[nodiscard]] std::add_lvalue_reference_t<Type> locked<Type, Lock, Mutex>::operator*() const noexcept
    {
        return m_value;
    }

    template <typename Type, template <typename> class Lock, typename Mutex>
    [[nodiscard]] std::add_pointer_t<Type> locked<Type, Lock, Mutex>::operator->() noexcept
    {
        return &m_value;
    }

    template <typename Type, template <typename> class Lock, typename Mutex>
    [[nodiscard]] std::add_pointer_t<Type> locked<Type, Lock, Mutex>::operator->() const noexcept
    {
        return &m_value;
    }
} // namespace lockpp