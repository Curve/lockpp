#pragma once

namespace lockpp
{
    template <typename T, typename Lock>
    class locked
    {
        template <typename, typename>
        friend class lock;

      private:
        Lock m_lock;
        T *m_value;

      protected:
        template <typename Mutex, typename... Ts>
        locked(T *, Mutex &, Ts &&...);

      public:
        [[nodiscard]] T &value() const &;
        [[nodiscard]] T &value() const && = delete;

      public:
        [[nodiscard]] T &operator*() const &;
        [[nodiscard]] T &operator*() const && = delete;

      public:
        [[nodiscard]] T *operator->() const &;
        [[nodiscard]] T *operator->() const && = delete;
    };
} // namespace lockpp

#include "locked.inl"
