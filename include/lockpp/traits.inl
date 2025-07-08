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

        template <typename T>
        struct lock_traits
        {
            using read_lock  = std::lock_guard<T>;
            using write_lock = std::lock_guard<T>;
        };

        template <SharedMutex T>
        struct lock_traits<T>
        {
            using read_lock  = std::shared_lock<T>;
            using write_lock = std::unique_lock<T>;
        };

        template <template <typename...> typename Wrapper, typename T>
        struct lock_traits<Wrapper<T>> : lock_traits<T>
        {
        };

        template <typename T>
        struct make_traits
        {
            static constexpr auto make()
            {
                return T{};
            }
        };

        template <typename T>
        struct make_traits<std::unique_ptr<T>>
        {
            static constexpr auto make()
            {
                return std::make_unique<T>();
            }
        };

        template <typename T>
        struct make_traits<std::shared_ptr<T>>
        {
            static constexpr auto make()
            {
                return std::make_shared<T>();
            }
        };
    } // namespace impl

    template <typename T>
    struct traits : impl::lock_traits<T>, impl::make_traits<T>
    {
    };
} // namespace lockpp
