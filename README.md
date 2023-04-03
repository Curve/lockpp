<div align="center"> 
    <img src="assets/logo.png" height=312>
</div>

<br/>

<p align="center"> 
    A C++20 library that provides mutex protection for any object
</p>

---

## ⚙️ Configuration
### Tests
```cmake
set(lockpp_tests OFF)
```
> If set to `ON`, lockpp will build tests.


## 📎 Installation

> **Note**  
> This library requires a C++20 capable compiler.
> In case you need support for C++17 checkout [version 1.0.2](https://github.com/Soundux/lockpp/releases/tag/v1.0.2)

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
#include <lockpp/lock.hpp>

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
#include <lockpp/lock.hpp>

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
#include <lockpp/lock.hpp>

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
