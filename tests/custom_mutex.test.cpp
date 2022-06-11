#include <catch2/catch.hpp>
#include <lockpp/lock.hpp>

TEST_CASE("Check if custom mutexes work", "[custom_mutex]")
{
    lockpp::lock<int, std::recursive_mutex> test(10);

    {
        auto read_1 = test.read();
        auto read_2 = test.read();
    }
    {
        auto read_1 = test.write();
        auto read_2 = test.write();
    }

    SUCCEED("No dead-lock caused because of recursive-mutex");
}