#include <catch2/catch.hpp>
#include <lock.hpp>

template <typename T> class allows_assign
{
    static auto test(...) -> std::uint8_t;
    template <typename O> static auto test(O *) -> decltype(std::declval<O>().assign(std::declval<std::unique_ptr<int> &>()), std::uint16_t{});

  public:
    static const bool value = sizeof(test(reinterpret_cast<T *>(0))) == sizeof(std::uint16_t);
};

template <typename T> class allows_copy
{
    static auto test(...) -> std::uint8_t;
    template <typename O> static auto test(O *) -> decltype(std::declval<O>().copy(), std::uint16_t{});

  public:
    static const bool value = sizeof(test(reinterpret_cast<T *>(0))) == sizeof(std::uint16_t);
};

TEST_CASE("Check if moveable-only types are handled correctly", "[moveable_types]")
{
    lockpp::lock<std::unique_ptr<int>> test(std::make_unique<int>(10));

    auto new_value = std::make_unique<int>(10);

    test.assign(std::move(new_value));

    REQUIRE(allows_copy<decltype(test)>::value == false);
    REQUIRE(allows_assign<decltype(test)>::value == false);
}