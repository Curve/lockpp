#pragma once
#include <type_traits>

namespace lockpp
{
    template <typename type_t, template <typename> class lock_t, typename mutex_t> class locked
    {
        template <typename, typename> friend class lock;

      private:
        lock_t<mutex_t> m_lock;
        std::add_lvalue_reference_t<type_t> m_value;

      protected:
        template <typename... lock_args_t> explicit locked(std::add_lvalue_reference_t<type_t>, mutex_t &, lock_args_t &&...);

      public:
        [[nodiscard]] std::add_lvalue_reference_t<type_t> operator*() noexcept;
        [[nodiscard]] std::add_lvalue_reference_t<type_t> operator*() const noexcept;

      public:
        [[nodiscard]] std::add_pointer_t<type_t> operator->() noexcept;
        [[nodiscard]] std::add_pointer_t<type_t> operator->() const noexcept;
    };
} // namespace lockpp

#include "locked.inl"