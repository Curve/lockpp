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
        template <template <typename> class Lock = read_lock, typename... Ts>
        [[nodiscard]] locked<const T, Lock<Mutex>> read(Ts &&...) const &;

        template <template <typename> class Lock = read_lock, typename... Ts>
        [[nodiscard]] locked<const T, Lock<Mutex>> read(Ts &&...) const && = delete;

      public:
        template <typename O>
            requires std::assignable_from<T &, O>
        void assign(O &&value) &;

      public:
        [[nodiscard]] T &get_unsafe() &;
        [[nodiscard]] T &get_unsafe() && = delete;

        [[nodiscard]] T &get_unsafe() const &;
        [[nodiscard]] T &get_unsafe() const && = delete;

      public:
        [[nodiscard]] T copy() const &;
        [[nodiscard]] T copy() const && = delete;
    };
} // namespace lockpp

#include "lock.inl"
