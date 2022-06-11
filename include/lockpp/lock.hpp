#pragma once
#include "locked.hpp"
#include "mutex_traits.hpp"
#include <mutex>
#include <shared_mutex>
#include <type_traits>

namespace lockpp
{
    template <typename type_t, typename mutex_t = std::shared_mutex> class lock
    {
        static_assert(std::is_same_v<std::decay_t<mutex_t>, mutex_t>);
        template <typename _m> using read_lock_t = std::conditional_t<is_shared_lockable<mutex_t>::value, std::shared_lock<_m>, std::lock_guard<_m>>;
        template <typename _m> using write_lock_t = std::conditional_t<is_shared_lockable<mutex_t>::value, std::unique_lock<_m>, std::lock_guard<_m>>;

      private:
        type_t m_value;
        mutable mutex_t m_mutex;

      public:
        template <typename... args_t> explicit lock(args_t &&...);

      public:
        template <template <typename> class lock_t = write_lock_t, typename... lock_args_t> [[nodiscard]] locked<type_t, lock_t, mutex_t> write(lock_args_t &&...);
        template <template <typename> class lock_t = read_lock_t, typename... lock_args_t> [[nodiscard]] locked<std::add_const_t<type_t>, lock_t, mutex_t> read(lock_args_t &&...) const;

      public:
        template <typename _type_t = type_t, typename = std::enable_if_t<std::is_move_assignable_v<_type_t>>> void assign(std::decay_t<type_t> &&);
        template <typename _type_t = type_t, typename = std::enable_if_t<std::is_copy_assignable_v<_type_t>>> void assign(const std::decay_t<type_t> &);

      public:
        [[nodiscard]] std::add_lvalue_reference_t<type_t> get_unsafe();
        [[nodiscard]] std::add_lvalue_reference_t<type_t> get_unsafe() const;

      public:
        template <typename _type_t = type_t, typename = std::enable_if_t<std::is_copy_constructible_v<_type_t>>> [[nodiscard]] std::decay_t<type_t> copy();
        template <typename _type_t = type_t, typename = std::enable_if_t<std::is_copy_constructible_v<_type_t>>> [[nodiscard]] std::decay_t<type_t> copy() const;
    };
} // namespace lockpp

#include "lock.inl"