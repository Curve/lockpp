#include "../lock/include/lock.hpp"
#include <iostream>
#include <mutex>
#include <thread>
#include <type_traits>
#include <vector>

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