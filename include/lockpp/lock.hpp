#pragma once

#include "traits.hpp"
#include "locked.hpp"

namespace lockpp
{
    template <typename T, typename Mutex = std::shared_mutex>
    class lock
    {
        template <typename>
        using read_lock = mutex_traits<Mutex>::read_lock;

        template <typename>
        using write_lock = mutex_traits<Mutex>::write_lock;

      private:
        T m_value;
        mutable Mutex m_mutex;

      public:
        template <typename... Ts>
        explicit lock(Ts &&...);

      public:
        template <template <typename> class Lock = write_lock, typename... Ts>
        [[nodiscard]] locked<T, Lock<Mutex>> write(Ts &&...) &;

      public:
        template <template <typename> class Lock = read_lock, typename Self, typename... Ts>
            requires std::is_lvalue_reference_v<Self>
        [[nodiscard]] locked<const T, Lock<Mutex>> read(this Self &&, Ts &&...);

      public:
        template <typename O>
            requires std::assignable_from<T &, O>
        void assign(O &&value) &;

      public:
        template <typename Self>
            requires std::is_lvalue_reference_v<Self>
        [[nodiscard]] T &get_unsafe(this Self &&);

      public:
        template <typename Self>
            requires std::is_lvalue_reference_v<Self> and std::copyable<T>
        [[nodiscard]] T copy(this Self &&);
    };
} // namespace lockpp

#include "lock.inl"
