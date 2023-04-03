#include <catch2/catch.hpp>
#include <lockpp/lock.hpp>

template <typename T, typename O>
concept allows_assign = requires(T &t, O &o) { t.assign(o); };

template <typename T>
concept allows_copy = requires(T &t) { t.copy(); };

TEST_CASE("Check if moveable-only types are handled correctly", "[moveable_types]")
{
    lockpp::lock<std::unique_ptr<int>> test(std::make_unique<int>(10));

    auto new_value = std::make_unique<int>(10);

    test.assign(std::move(new_value));

    REQUIRE(allows_copy<decltype(test)> == false);
    REQUIRE(allows_assign<decltype(test), const std::unique_ptr<int> &> == false);
}