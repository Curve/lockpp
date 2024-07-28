#pragma once

#include <mutex>
#include <shared_mutex>

namespace lockpp
{
    template <typename T>
    concept is_shared = requires(T &mutex) {
        { mutex.lock_shared() };
    };

    template <typename T>
    struct mutex_traits
    {
        using read_lock  = std::lock_guard<T>;
        using write_lock = std::lock_guard<T>;
    };

    template <typename T>
        requires is_shared<T>
    struct mutex_traits<T>
    {
        using read_lock  = std::shared_lock<T>;
        using write_lock = std::unique_lock<T>;
    };
} // namespace lockpp
