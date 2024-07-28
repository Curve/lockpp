#include <boost/ut.hpp>

#include <lockpp/lock.hpp>

using namespace boost::ut;
using namespace boost::ut::bdd;

// NOLINTNEXTLINE
suite<"basic"> assign_copy_suite = []()
{
    lockpp::lock<std::string> test("a");

    should("be assignable") = [&]
    {
        test.assign("");
        expect(test.get_unsafe().empty());

        test.assign("b");
        expect(test.get_unsafe() == "b");
    };

    should("be copyable") = [&]
    {
        expect(test.copy() == "b");

        test.copy().clear();
        expect(test.get_unsafe() == "b");
    };

    should("be readable") = [&]
    {
        auto locked = test.read();

        expect(*locked == "b");
        expect(locked.value() == "b");
        expect(std::same_as<decltype(*locked), const std::string &>);
    };

    should("be writable") = [&]
    {
        auto locked = test.write();
        locked->clear();

        expect(locked->empty());
        expect(locked.value().empty());
        expect(test.get_unsafe().empty());

        expect(std::same_as<decltype(*locked), std::string &>);
    };
};
