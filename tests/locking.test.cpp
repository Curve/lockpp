#define CONFIG_CATCH_MAIN
#include <catch2/catch.hpp>
#include <future>
#include <lockpp/lock.hpp>
#include <thread>

TEST_CASE("Check if simultaneous access causes dead-lock", "[locking]")
{
    using namespace std::chrono_literals;

    //? Ugly hack to make this test work...
    bool success = false;
    auto test_case = std::thread([&success]() {
        lockpp::lock<int> test_int(10);

        auto locked = test_int.read();
        test_int.assign(*locked); //? This should dead-lock!

        success = true;
    });
    test_case.detach();

    std::this_thread::sleep_for(5s);
    REQUIRE(success == false);

    lockpp::lock<int> test(10);
    {
        auto write_lock = test.write();
        test.get_unsafe() = 0;
    }
    REQUIRE(*test.read() == 0);
}