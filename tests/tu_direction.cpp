
#include <iostream>

#include "catch.hpp"
#include "direction.hpp"

/**
 * @test Test des variables globale constante des principales directions
 */
TEST_CASE("Test directions principales")
{
    REQUIRE(Nord == Vector2i(0, -2));
    REQUIRE(NordOuest == Vector2i(-1, -1));
    REQUIRE(SudOuest == Vector2i(-1, +1));
    REQUIRE(Sud == Vector2i(0, +2));
    REQUIRE(SudEst == Vector2i(0, +1));
    REQUIRE(NordEst == Vector2i(0, -1));
    REQUIRE(NullDirection == Vector2i(0, 0));
}