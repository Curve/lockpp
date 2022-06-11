#pragma once

namespace lockpp
{
    template <typename type_t, typename mutex_t> template <typename... args_t> lock<type_t, mutex_t>::lock(args_t &&...args) : m_value(std::forward<args_t>(args)...) {}

    template <typename type_t, typename mutex_t>
    template <template <typename> class lock_t, typename... lock_args_t>
    locked<type_t, lock_t, mutex_t> lock<type_t, mutex_t>::write(lock_args_t &&...lock_args)
    {
        return locked<type_t, lock_t, mutex_t>(m_value, m_mutex, std::forward<lock_args_t>(lock_args)...);
    }

    template <typename type_t, typename mutex_t>
    template <template <typename> class lock_t, typename... lock_args_t>
    locked<std::add_const_t<type_t>, lock_t, mutex_t> lock<type_t, mutex_t>::read(lock_args_t &&...lock_args) const
    {
        return locked<std::add_const_t<type_t>, lock_t, mutex_t>(m_value, m_mutex, std::forward<lock_args_t>(lock_args)...);
    }

    template <typename type_t, typename mutex_t> template <typename, typename> void lock<type_t, mutex_t>::assign(std::decay_t<type_t> &&value)
    {
        *write() = std::move(value);
    }

    template <typename type_t, typename mutex_t> template <typename, typename> void lock<type_t, mutex_t>::assign(const std::decay_t<type_t> &value)
    {
        *write() = value;
    }

    template <typename type_t, typename mutex_t> std::add_lvalue_reference_t<type_t> lock<type_t, mutex_t>::get_unsafe()
    {
        return m_value;
    }

    template <typename type_t, typename mutex_t> std::add_lvalue_reference_t<type_t> lock<type_t, mutex_t>::get_unsafe() const
    {
        return m_value;
    }

    template <typename type_t, typename mutex_t> template <typename, typename> std::decay_t<type_t> lock<type_t, mutex_t>::copy()
    {
        return *read();
    }

    template <typename type_t, typename mutex_t> template <typename, typename> std::decay_t<type_t> lock<type_t, mutex_t>::copy() const
    {
        return *read();
    }
} // namespace lockpp