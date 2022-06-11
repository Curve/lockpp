#pragma once

namespace lockpp
{
    template <typename type_t, template <typename> class lock_t, typename mutex_t>
    template <typename... lock_args_t>
    locked<type_t, lock_t, mutex_t>::locked(std::add_lvalue_reference_t<type_t> value, mutex_t &mutex, lock_args_t &&...lock_args)
        : m_lock(mutex, std::forward<lock_args_t>(lock_args)...), m_value(value)
    {
    }

    template <typename type_t, template <typename> class lock_t, typename mutex_t>
    [[nodiscard]] std::add_lvalue_reference_t<type_t> locked<type_t, lock_t, mutex_t>::operator*() noexcept
    {
        return m_value;
    }

    template <typename type_t, template <typename> class lock_t, typename mutex_t>
    [[nodiscard]] std::add_lvalue_reference_t<type_t> locked<type_t, lock_t, mutex_t>::operator*() const noexcept
    {
        return m_value;
    }

    template <typename type_t, template <typename> class lock_t, typename mutex_t> [[nodiscard]] std::add_pointer_t<type_t> locked<type_t, lock_t, mutex_t>::operator->() noexcept
    {
        return &m_value;
    }

    template <typename type_t, template <typename> class lock_t, typename mutex_t> [[nodiscard]] std::add_pointer_t<type_t> locked<type_t, lock_t, mutex_t>::operator->() const noexcept
    {
        return &m_value;
    }
} // namespace lockpp