#define CONFIG_CATCH_MAIN
#include <catch2/catch_test_macros.hpp>

TEST_CASE("This is a test test case", "[test]")
{
    REQUIRE(true);
}