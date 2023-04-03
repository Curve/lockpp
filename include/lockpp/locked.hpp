#pragma once
#include "traits.hpp"

namespace lockpp
{
    template <typename Type, template <typename> class Lock, typename Mutex> //
    class locked
    {
        template <typename, decayed_type> friend class lock;

      private:
        Lock<Mutex> m_lock;
        std::add_lvalue_reference_t<Type> m_value;

      protected:
        template <typename... LockArgs> //
        explicit locked(std::add_lvalue_reference_t<Type>, Mutex &, LockArgs &&...);

      public:
        [[nodiscard]] std::add_lvalue_reference_t<Type> operator*() noexcept;
        [[nodiscard]] std::add_lvalue_reference_t<Type> operator*() const noexcept;

      public:
        [[nodiscard]] std::add_pointer_t<Type> operator->() noexcept;
        [[nodiscard]] std::add_pointer_t<Type> operator->() const noexcept;
    };
} // namespace lockpp

#include "locked.inl"