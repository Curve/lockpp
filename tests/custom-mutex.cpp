#include <boost/ut.hpp>
#include <lockpp/lock.hpp>

using namespace boost::ut;
using namespace boost::ut::bdd;

// NOLINTNEXTLINE
suite<"custom-mutex"> custom_mutex_suite = []()
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
