#pragma once
#include "traits.hpp"
#include <mutex>
#include <shared_mutex>

namespace sxl
{
    template <typename var_t, typename mutex_t = std::shared_mutex>
    class lock
    {
        template <bool is_const, typename guard_t, typename... Args>
        class locked
        {
            using cond_var = std::conditional_t<is_const, const var_t &, var_t &>;

          private:
            mutable guard_t lock;
            cond_var value;

          public:
            locked(mutex_t &mutex, cond_var val, Args &&...args) : lock(mutex, std::forward<Args>(args)...), value(val)
            {}

            locked(locked &&) = delete;
            locked(const locked &) = delete;
            locked &operator=(locked &&) = delete;
            locked &operator=(const locked &) = delete;

          public:
            auto &operator*() const noexcept
            {
                return value;
            }
            auto &operator*() noexcept
            {
                return value;
            }
            auto *operator->() const noexcept
            {
                return &value;
            }
            auto *operator->() noexcept
            {
                return &value;
            }
        };

      private:
        var_t value;
        mutable mutex_t mutex;

        using read_lock = std::conditional_t<traits::is_read_lock<mutex_t>::value, std::shared_lock<mutex_t>,
                                             std::lock_guard<mutex_t>>;
        using write_lock = std::conditional_t<traits::is_read_lock<mutex_t>::value, std::unique_lock<mutex_t>,
                                              std::lock_guard<mutex_t>>;

      public:
        template <typename... T>
        explicit lock(T &&...args) : value{std::forward<T>(args)...}
        {}

        lock(lock &&) = delete;
        lock(const lock &) = delete;
        lock &operator=(lock &&) = delete;
        lock &operator=(const lock &) = delete;

      public:
        template <class guard_t = read_lock, typename... Args>
        std::decay_t<var_t> copy(Args &&...args) const
        {
            return *locked<true, guard_t>(mutex, value, std::forward<Args>(args)...);
        }

        template <class guard_t = write_lock, typename... Args>
        void assign(const var_t &newValue, Args &&...args)
        {
            *locked<false, guard_t>(mutex, value, std::forward<Args>(args)...) = newValue;
        }

        template <class guard_t = read_lock, typename... Args>
        auto read(Args &&...args) const
        {
            return locked<true, guard_t>(mutex, value, std::forward<Args>(args)...);
        }

        template <class guard_t = write_lock, typename... Args>
        auto write(Args &&...args)
        {
            return locked<false, guard_t>(mutex, value, std::forward<Args>(args)...);
        }

        auto &unsafe()
        {
            return value;
        }
    };
} // namespace sxl