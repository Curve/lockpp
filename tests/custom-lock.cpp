#include <boost/ut.hpp>

#include <future>
#include <lockpp/lock.hpp>

using namespace boost::ut;
using namespace boost::ut::bdd;

// NOLINTNEXTLINE
suite<"custom-lock"> custom_lock_suite = []()
{
    lockpp::lock<int> test(10);

    should("allow shared read") = [&]
    {
        auto read_1 = test.read();
        auto read_2 = test.read();
    };

    should("allow double unique with adoption") = [&]
    {
        auto read_1 = test.read<std::unique_lock>();
        auto read_2 = test.read<std::unique_lock>(std::adopt_lock);
    };

    should("deadlock") = [&]
    {
        std::promise<bool> result;

        std::thread thread{[&]
                           {
                               try
                               {
                                   auto read_1 = test.read<std::unique_lock>();
                                   auto read_2 = test.read<std::unique_lock>();

                                   result.set_value(true);
                               }
                               catch (...)
                               {
                               }
                           }};

        thread.detach();

        auto status = result.get_future().wait_for(std::chrono::seconds(5));
        expect(status != std::future_status::ready);
    };
};
