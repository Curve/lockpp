#pragma once
#include <utility>
#include <concepts>

namespace lockpp
{
    template <typename T>
    concept shared_lockable = requires(T &mutex) { mutex.lock_shared(); };

    template <typename T>
    concept decayed_type = std::is_same_v<T, std::decay_t<T>>;

    template <template <typename> typename Lock, typename Mutex, typename... Args>
    concept valid_arguments = requires(Mutex &mutex, Args &&...args) {
        Lock<Mutex>{mutex, std::forward<Args>(args)...};
    };
} // namespace lockpp