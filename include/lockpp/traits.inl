#pragma once

#include "traits.hpp"

#include <mutex>
#include <shared_mutex>

#include <memory>

namespace lockpp
{
    namespace impl
    {
        template <typename T>
        concept SharedMutex = requires(T &mutex) {
            { mutex.lock_shared() };
        };
    } // namespace impl

    template <typename T>
    struct lock_traits
    {
        using read_lock  = std::lock_guard<T>;
        using write_lock = std::lock_guard<T>;
    };

    template <impl::SharedMutex T>
    struct lock_traits<T>
    {
        using read_lock  = std::shared_lock<T>;
        using write_lock = std::unique_lock<T>;
    };

    template <typename T>
    struct traits : lock_traits<T>
    {
        using mutex = T;

      public:
        static constexpr auto make()
        {
            return T{};
        }
    };

    template <typename T>
    struct traits<std::unique_ptr<T>> : lock_traits<T>
    {
        using mutex = T;

      public:
        static constexpr auto make()
        {
            return std::make_unique<T>();
        }
    };

    template <typename T>
    struct traits<std::shared_ptr<T>> : lock_traits<T>
    {
        using mutex = T;

      public:
        static constexpr auto make()
        {
            return std::make_shared<T>();
        }
    };
} // namespace lockpp
