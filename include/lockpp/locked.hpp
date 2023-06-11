#pragma once
#include "traits.hpp"

namespace lockpp
{
    template <typename Type, template <typename> class Lock, typename Mutex> //
    class locked
    {
        template <typename, decayed_type> friend class lock;

      private:
        Type &m_value;
        Lock<Mutex> m_lock;

      protected:
        template <typename... LockArgs> //
        explicit locked(Type &, Mutex &, LockArgs &&...);

      public:
        [[nodiscard]] Type &operator*() noexcept;
        [[nodiscard]] Type &operator*() const noexcept;

      public:
        [[nodiscard]] Type *operator->() noexcept;
        [[nodiscard]] Type *operator->() const noexcept;
    };
} // namespace lockpp

#include "locked.inl"