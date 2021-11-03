
<h1 align="center"> 🔐 lockpp </h1>
<p align="center">
A C++17 library that provides mutex protection for objects
</p>

<p align="center">
    <a href="https://github.com/Soundux/lockpp/actions">
        <img src="https://img.shields.io/github/workflow/status/Soundux/lockpp/Test%20on%20Linux?label=Linux%20Build&style=flat-square" alt="Linux Build" />
    </a>
    <a href="https://github.com/Soundux/lockpp/actions">
        <img src="https://img.shields.io/github/workflow/status/Soundux/lockpp/Test%20on%20Windows?label=Windows%20Build&style=flat-square" alt="Windows Build" />
    </a>
    <a href="https://github.com/Soundux/lockpp/blob/master/LICENSE">
        <img src="https://img.shields.io/github/license/Curve/imgui-cmake.svg?style=flat-square" alt="License" />
    </a>
</p>

---

## ⚙️ Configuration
### Tests
```cmake
set(lockpp_tests OFF)
```
> If set to `ON`, lockpp will build tests.


## 📎 Installation
- FetchContent
    ```cmake
    include(FetchContent)
    FetchContent_Declare(lockpp GIT_REPOSITORY "https://github.com/Soundux/lockpp")

    FetchContent_MakeAvailable(lockpp)
    target_link_libraries(<YourLibrary> lockpp)
    ```
- Git Submodule
    ```bash
    git submodule add "https://github.com/Soundux/lockpp"
    ```
    ```cmake
    # Somewhere in your CMakeLists.txt
    add_subdirectory("<path_to_lockpp>")
    target_link_libraries(<YourLibrary> lockpp)
    ```

## 📔 Usage

### Simple example
```cpp
#include <lock.hpp>

int main()
{
    lockpp::lock<std::string> protected_string("Test");
    {
        auto read_access = protected_string.read();
        bool is_empty = read_access->empty();
        // read_access->clear(); <-- Will not work
    }
    {
        auto write_access = protected_string.write();

        write_access->clear();
        *write_access = "New String!";

        // auto another_write_access = protected_string.write(); <-- This will lock.
    }

    return 0;
}
```

### Custom Mutex
```cpp
#include <lock.hpp>

int main()
{
    lockpp::lock<std::string, std::recursive_mutex> protected_string("Test");
    {
        auto write_access = protected_string.write();

        write_access->clear();
        *write_access = "New String!";

        auto another_write_access = protected_string.write();
        *another_write_access = "This is fine!";
    }

    return 0;
}
```

### Custom Locks
```cpp
#include <lock.hpp>

int main()
{
    lockpp::lock<std::string> protected_string("Test");
    {
        auto read_1 = test.read<std::unique_lock>();
        auto read_2 = test.read<std::unique_lock>(std::adopt_lock); // <-- Also accepts custom arguments for lock
    }

    return 0;
}
```

> For more examples see [tests](tests/)