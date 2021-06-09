## lockpp
A cross-platform C++17 library that manages mutex protection for objects.

## Usage

- Add the library to your project
  - ```cmake
    add_subdirectory(/path/to/lockpp)
    link_libraries(lockpp)
    ```

## Example
```cpp
#include <iostream>
#include <lock.hpp>
#include <string>

int main()
{
    sxl::lock<std::string> test("Test");

    {
        // Test is now locked until the scope is exited.
        auto writeAccess = test.write();

        writeAccess->append("1");
        *writeAccess = "Some other test";
    }

    {
        auto readAccess = test.read();
        // readAccess->append("Test"); //! Won't work, is append is not const
        std::cout << *readAccess << std::endl;
    }

    return 0;
}
```
