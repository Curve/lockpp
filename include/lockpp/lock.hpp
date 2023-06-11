#pragma once
#include "traits.hpp"
#include "locked.hpp"

#include <mutex>
#include <type_traits>
#include <shared_mutex>

namespace lockpp
{
    template <typename Type, decayed_type Mutex = std::shared_mutex> class lock
    {
        template <decayed_type M, template <typename> typename T, template <typename> typename O> //
        using shared_or = std::conditional_t<shared_lockable<Mutex>, T<M>, O<M>>;

        template <decayed_type M> //
        using read_lock = shared_or<M, std::shared_lock, std::lock_guard>;

        template <decayed_type M> //
        using write_lock = shared_or<M, std::unique_lock, std::lock_guard>;

      private:
        Type m_value;
        mutable Mutex m_mutex;

      public:
        template <typename... Args> explicit lock(Args &&...);

      public:
        template <template <typename> class Lock = write_lock, typename... LockArgs>
            requires valid_arguments<Lock, Mutex, LockArgs...>
        [[nodiscard]] locked<Type, Lock, Mutex> write(LockArgs &&...);

      public:
        template <template <typename> class Lock = read_lock, typename... LockArgs>
            requires valid_arguments<Lock, Mutex, LockArgs...>
        [[nodiscard]] locked<std::add_const_t<Type>, Lock, Mutex> read(LockArgs &&...) const;

      public:
        void assign(Type &&)
            requires std::is_move_assignable_v<Type>;

      public:
        void assign(const Type &)
            requires std::is_copy_assignable_v<Type>;

      public:
        [[nodiscard]] Type &get_unsafe();
        [[nodiscard]] Type &get_unsafe() const;

      public:
        [[nodiscard]] Type copy()
            requires std::is_copy_constructible_v<Type>;

      public:
        [[nodiscard]] Type copy() const
            requires std::is_copy_constructible_v<Type>;
    };
} // namespace lockpp

#include "lock.inl"