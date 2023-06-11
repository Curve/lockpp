#pragma once
#include "lock.hpp"

namespace lockpp
{
    template <typename Type, decayed_type Mutex>
    template <typename... Args>
    lock<Type, Mutex>::lock(Args &&...args) : m_value(std::forward<Args>(args)...)
    {
    }

    template <typename Type, decayed_type Mutex>
    template <template <typename> class Lock, typename... LockArgs>
        requires valid_arguments<Lock, Mutex, LockArgs...>
    locked<Type, Lock, Mutex> lock<Type, Mutex>::write(LockArgs &&...lock_args)
    {
        return locked<Type, Lock, Mutex>{m_value, m_mutex, std::forward<LockArgs>(lock_args)...};
    }

    template <typename Type, decayed_type Mutex>
    template <template <typename> class Lock, typename... LockArgs>
        requires valid_arguments<Lock, Mutex, LockArgs...>
    locked<std::add_const_t<Type>, Lock, Mutex> lock<Type, Mutex>::read(LockArgs &&...lock_args) const
    {
        return locked<std::add_const_t<Type>, Lock, Mutex>{m_value, m_mutex, std::forward<LockArgs>(lock_args)...};
    }

    template <typename Type, decayed_type Mutex>
    void lock<Type, Mutex>::assign(Type &&value)
        requires std::is_move_assignable_v<Type>
    {
        *write() = std::move(value);
    }

    template <typename Type, decayed_type Mutex>
    void lock<Type, Mutex>::assign(const Type &value)
        requires std::is_copy_assignable_v<Type>
    {
        *write() = value;
    }

    template <typename Type, decayed_type Mutex> //
    Type &lock<Type, Mutex>::get_unsafe()
    {
        return m_value;
    }

    template <typename Type, decayed_type Mutex> //
    Type &lock<Type, Mutex>::get_unsafe() const
    {
        return m_value;
    }

    template <typename Type, decayed_type Mutex>
    Type lock<Type, Mutex>::copy()
        requires std::is_copy_constructible_v<Type>
    {
        return *read();
    }

    template <typename Type, decayed_type Mutex>
    Type lock<Type, Mutex>::copy() const
        requires std::is_copy_constructible_v<Type>
    {
        return *read();
    }
} // namespace lockpp