#include <catch2/catch.hpp>
#include <lockpp/lock.hpp>
#include <string>

TEST_CASE("Check assign & copy", "[assign_copy]")
{
    lockpp::lock<std::string> test("Test");

    test.assign("");
    REQUIRE(test.copy().empty());
}