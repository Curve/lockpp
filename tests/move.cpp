#include <boost/ut.hpp>

#include <lockpp/lock.hpp>

using namespace boost::ut;
using namespace boost::ut::literals;

template <typename T, typename O>
concept can_assign = requires(T value, O &&other) { value.assign(std::forward<O>(other)); };

// NOLINTNEXTLINE
suite<"move"> move_suite = []()
{
    lockpp::lock<std::unique_ptr<int>> test{std::make_unique<int>(10)};
    auto other = std::make_unique<int>(20);

    using T = decltype(test);

    expect(can_assign<T, std::unique_ptr<int> &&>);
    expect(not can_assign<T, std::unique_ptr<int> &>);
    expect(not can_assign<T, const std::unique_ptr<int> &>);

    test.assign(std::move(other));
    {
        auto locked = test.read();
        expect(**locked == 20);
    }
};
