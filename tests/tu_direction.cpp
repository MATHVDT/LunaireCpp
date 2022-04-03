/**
 * @file tu_direction.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Fichier tests unitaires pour les vecteurs des directions principales
 * @details Voir image *carte_hexagonale_direction.png* pour plus d'information sur la gestion de la carte
 * @version 0.1
 * @date 2022-03-31
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>

#include "catch.hpp"
#include "direction.hpp"

/**
 * @test Test des variables globale constante des principales directions
 */
TEST_CASE("Test directions principales")
{
    REQUIRE(Nord == Vector2i(0, -1));
    REQUIRE(NordOuest == Vector2i(-1, -1));
    REQUIRE(SudOuest == Vector2i(-1, 0));
    REQUIRE(Sud == Vector2i(0, +1));
    REQUIRE(SudEst == Vector2i(1, 0));
    REQUIRE(NordEst == Vector2i(1, -1));
    REQUIRE(NullDirection == Vector2i(0, 0));
}

/**
 * @test Addictions des directions principales sur un veteur position *(cf. carte_hexagonale_direction.png)*
 *
 */
TEST_CASE("Deplacement dans les directions principales")
{
    Vector2i pos{3, 2};
    REQUIRE(pos.x == 3);
    REQUIRE(pos.y == 2);

    SECTION("Nord")
    {
        pos = pos + Nord;
        REQUIRE(pos.x == 3);
        REQUIRE(pos.y == 1);
    }
    SECTION("NordOuest")
    {
        pos = pos + NordOuest;
        REQUIRE(pos.x == 2);
        REQUIRE(pos.y == 1);
    }
    SECTION("SudOuest")
    {
        pos = pos + SudOuest;
        REQUIRE(pos.x == 2);
        REQUIRE(pos.y == 2);
    }
    SECTION("Sud")
    {
        pos = pos + Sud;
        REQUIRE(pos.x == 3);
        REQUIRE(pos.y == 3);
    }
    SECTION("SudEst")
    {
        pos = pos + SudEst;
        REQUIRE(pos.x == 4);
        REQUIRE(pos.y == 2);
    }
    SECTION("NordEst")
    {
        pos = pos + NordEst;
        REQUIRE(pos.x == 4);
        REQUIRE(pos.y == 1);
    }
}

TEST_CASE("Directions opposées")
{
    REQUIRE(directionOpposee(Nord) == Sud);
    REQUIRE(directionOpposee(NordOuest) == SudEst);
    REQUIRE(directionOpposee(SudOuest) == NordEst);
    REQUIRE(directionOpposee(Sud) ==Nord);
    REQUIRE(directionOpposee(SudEst) == NordOuest);
    REQUIRE(directionOpposee(NordEst) == SudOuest);
    REQUIRE(directionOpposee(NullDirection) == NullDirection);
    REQUIRE(directionOpposee(Vector2i(2,1)) == NullDirection);
}