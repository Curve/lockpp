#include <boost/ut.hpp>

#include <lockpp/lock.hpp>

using namespace boost::ut;
using namespace boost::ut::bdd;

// NOLINTNEXTLINE
suite<"custom-mutex"> custom_mutex_suite = []()
{
    "recursive_mutex"_test = []
    {
        lockpp::lock<int, std::recursive_mutex> test(10);

        should("not deadlock") = [&]
        {
            auto read_1 = test.read();
            auto read_2 = test.read();

            auto write_1 = test.write();
            auto write_2 = test.write();

            expect(true);
        };
    };

    "unique_ptr_mutex"_test = []
    {
        lockpp::lock<int, std::unique_ptr<std::shared_mutex>> test(10);

        should("deduce traits") = [&]
        {
            using lock_t  = decltype(test);
            using mutex_t = std::shared_mutex;

            expect(std::same_as<lock_t::read_lock<mutex_t>, std::shared_lock<mutex_t>>);
            expect(std::same_as<lock_t::write_lock<mutex_t>, std::unique_lock<mutex_t>>);
        };

        should("be movable") = [&]
        {
            auto test2 = std::move(test);
            expect(eq(test2.copy(), 10));
        };
    };
};
