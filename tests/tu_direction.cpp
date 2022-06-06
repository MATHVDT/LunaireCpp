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
 *
 *  @deprecated Changement de gestion des directions
 */
/*
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
*/

/**
 * @test Addictions des directions principales sur un veteur position *(cf. carte_hexagonale_direction.png)*
 *
 * @deprecated Changement de gestion des directions
 */
/*
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
*/

/**
 * @brief
 *
 * @deprecated Changement de gestion des directions
 */
/*
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
*/

/**
 * @brief Test de la gestion des directions
 *
 */
TEST_CASE("Test calcul case voisine")
{
    Vector2i position1 = Vector2i{0, 0};
    Vector2i position2 = Vector2i{2, 1};
    Vector2i position3 = Vector2i{3, 1};
    Vector2i position4 = Vector2i{2, 2};
    Vector2i position5 = Vector2i{3, 2};

    SECTION("NORD")
    {
        REQUIRE(positionCaseVoisineNORD(position1) == Vector2i(0, -1));
        REQUIRE(positionCaseVoisineNORD(position2) == Vector2i(2, 0));
        REQUIRE(positionCaseVoisineNORD(position3) == Vector2i(3, 0));
        REQUIRE(positionCaseVoisineNORD(position4) == Vector2i(2, 1));
        REQUIRE(positionCaseVoisineNORD(position5) == Vector2i(3, 1));
    }

    SECTION("NORDOUEST")
    {
        REQUIRE(positionCaseVoisineNORDOUEST(position1) == Vector2i(-1, 0));
        REQUIRE(positionCaseVoisineNORDOUEST(position2) == Vector2i(1, 1));
        REQUIRE(positionCaseVoisineNORDOUEST(position3) == Vector2i(2, 0));
        REQUIRE(positionCaseVoisineNORDOUEST(position4) == Vector2i(1, 2));
        REQUIRE(positionCaseVoisineNORDOUEST(position5) == Vector2i(2, 1));
    }

    SECTION("SUDOUEST")
    {
        REQUIRE(positionCaseVoisineSUDOUEST(position1) == Vector2i(-1, 1));
        REQUIRE(positionCaseVoisineSUDOUEST(position2) == Vector2i(1, 2));
        REQUIRE(positionCaseVoisineSUDOUEST(position3) == Vector2i(2, 1));
        REQUIRE(positionCaseVoisineSUDOUEST(position4) == Vector2i(1, 3));
        REQUIRE(positionCaseVoisineSUDOUEST(position5) == Vector2i(2, 2));
    }

    SECTION("SUD")
    {
        REQUIRE(positionCaseVoisineSUD(position1) == Vector2i(0, 1));
        REQUIRE(positionCaseVoisineSUD(position2) == Vector2i(2, 2));
        REQUIRE(positionCaseVoisineSUD(position3) == Vector2i(3, 2));
        REQUIRE(positionCaseVoisineSUD(position4) == Vector2i(2, 3));
        REQUIRE(positionCaseVoisineSUD(position5) == Vector2i(3, 3));
    }

    SECTION("SUDEST")
    {
        REQUIRE(positionCaseVoisineSUDEST(position1) == Vector2i(1, 1));
        REQUIRE(positionCaseVoisineSUDEST(position2) == Vector2i(3, 2));
        REQUIRE(positionCaseVoisineSUDEST(position3) == Vector2i(4, 1));
        REQUIRE(positionCaseVoisineSUDEST(position4) == Vector2i(3, 3));
        REQUIRE(positionCaseVoisineSUDEST(position5) == Vector2i(4, 2));
    }

    SECTION("NORDEST")
    {
        REQUIRE(positionCaseVoisineNORDEST(position1) == Vector2i(1, 0));
        REQUIRE(positionCaseVoisineNORDEST(position2) == Vector2i(3, 1));
        REQUIRE(positionCaseVoisineNORDEST(position3) == Vector2i(4, 0));
        REQUIRE(positionCaseVoisineNORDEST(position4) == Vector2i(3, 2));
        REQUIRE(positionCaseVoisineNORDEST(position5) == Vector2i(4, 1));
    }
}