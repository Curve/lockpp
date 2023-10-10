#include <boost/ut.hpp>
#include <lockpp/lock.hpp>

using namespace boost::ut;
using namespace boost::ut::literals;

template <typename T, typename O>
concept allows_assign = requires(T t, O &&o) { t.assign(std::forward<O>(o)); };

template <typename T>
concept allows_copy = requires(T &t) { t.copy(); };

// NOLINTNEXTLINE
suite<"move"> move_suite = []()
{
    auto test = lockpp::lock{std::make_unique<int>(10)};
    auto other = std::make_unique<int>(20);

    using test_t = decltype(test);

    expect(not allows_copy<test_t>);

    expect(allows_assign<test_t, std::unique_ptr<int> &&>);
    expect(not allows_assign<test_t, const std::unique_ptr<int> &>);

    test.assign(std::move(other));
    expect(**test.read() == 20);
};
