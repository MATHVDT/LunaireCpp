
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

TEST_CASE("Deplacement dans les directions principales")
{
    Vector2i pos{1, 4};

    REQUIRE(pos.x == 1);
    REQUIRE(pos.y == 4);

    SECTION("Nord")
    {
        pos = pos + Nord;
        REQUIRE(pos.x == 1);
        REQUIRE(pos.y == 2);
    }
    SECTION("NordOuest")
    {
        pos = pos + NordOuest;
        REQUIRE(pos.x == 0);
        REQUIRE(pos.y == 3);
    }
    SECTION("SudOuest")
    {
        pos = pos + SudOuest;
        REQUIRE(pos.x == 0);
        REQUIRE(pos.y == 5);
    }
    SECTION("Sud")
    {
        pos = pos + Sud;
        REQUIRE(pos.x == 1);
        REQUIRE(pos.y == 6);
    }

    SECTION("SudEst")
    {
        pos = pos + SudEst;
        REQUIRE(pos.x == 1);
        REQUIRE(pos.y == 5);
    }

    SECTION("NordEst")
    {
        pos = pos + NordEst;
        REQUIRE(pos.x == 1);
        REQUIRE(pos.y == 3);
    }
}