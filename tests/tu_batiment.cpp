#include <iostream>
#include <sstream>
#include <cstring>
#include <list>

#include "catch.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include "Structure.hpp"
#include "Batiment.hpp"
#include "direction.hpp"

using namespace std;
using namespace sf;

ContextGlobal &contextGlobal = ContextGlobal::getInstance();

TEST_CASE("Test création batiment")
{
    float eps = 0.0001;
    Vector2f vectPos{0.f, 0.f};
    Batiment bat{Vector2f(vectPos)};

    REQUIRE(bat.getNbStructures() == 1);
    REQUIRE(bat.getNbBatiments() == 1);

    REQUIRE(bat.getIdStructure() == 0);
    REQUIRE(bat.getIdBatiment() == 0);

    REQUIRE(bat.getPosition().x == Approx(vectPos.x).epsilon(eps));
    REQUIRE(bat.getPosition().y == Approx(vectPos.y).epsilon(eps));

    Batiment bat2{Vector2f(1.5f, 4.4f)};

    REQUIRE(bat2.getNbStructures() == 2);
    REQUIRE(bat2.getNbBatiments() == 2);

    REQUIRE(bat2.getIdStructure() == 1);
    REQUIRE(bat2.getIdBatiment() == 1);

    REQUIRE(bat2.getPosition().x == Approx(1.5f).epsilon(eps));
    REQUIRE(bat2.getPosition().y == Approx(4.4f).epsilon(eps));
}

TEST_CASE("Connexion batiment")
{
    float eps = 0.0001;
    Vector2f vectPos{0.f, 0.f};
    Batiment bat{Vector2f(vectPos)};

    SECTION("Test aucune connexion")
    {
        REQUIRE(bat.getNbConnexions() == 0);
        REQUIRE(bat.getNbEntrees() == 0);

        REQUIRE(bat.getConnexionDirection(static_cast<Vector2i>(vectPos)) == ConnexionNull);
        REQUIRE(bat.getConnexionDirection(Nord) == ConnexionNull);
        REQUIRE(bat.getConnexionDirection(NordOuest) == ConnexionNull);
        REQUIRE(bat.getConnexionDirection(SudOuest) == ConnexionNull);
        REQUIRE(bat.getConnexionDirection(Sud) == ConnexionNull);
        REQUIRE(bat.getConnexionDirection(SudEst) == ConnexionNull);
        REQUIRE(bat.getConnexionDirection(NordEst) == ConnexionNull);

        REQUIRE(bat.getConnexionDirection(NULLDIRECTION) == ConnexionNull);
        REQUIRE(bat.getConnexionDirection(NORD) == ConnexionNull);
        REQUIRE(bat.getConnexionDirection(NORDOUEST) == ConnexionNull);
        REQUIRE(bat.getConnexionDirection(SUDOUEST) == ConnexionNull);
        REQUIRE(bat.getConnexionDirection(SUD) == ConnexionNull);
        REQUIRE(bat.getConnexionDirection(SUDEST) == ConnexionNull);
        REQUIRE(bat.getConnexionDirection(NORDEST) == ConnexionNull);

        REQUIRE(bat.getConnexionsEntrantes() == list<connexion_t>{});
        REQUIRE(bat.getConnexions() == list<connexion_t>{});
        REQUIRE(bat.getConnexionSortie() == ConnexionNull);
    }
    SECTION("Test ajout batiment")
    {
        bat.getConnexionDirection(NordEst);
    }
}