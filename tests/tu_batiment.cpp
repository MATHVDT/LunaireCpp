#include <iostream>
#include <sstream>
#include <cstring>

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

    // REQUIRE(bat.getNbStructures() == 1);
    // REQUIRE(bat.getNbBatiments() == 1);

    // REQUIRE(bat.getIdStructure() == 0);
    // REQUIRE(bat.getIdBatiment() == 0);

    // REQUIRE(bat.getPosition().x == Approx(vectPos.x).epsilon(eps));
    // REQUIRE(bat.getPosition().y == Approx(vectPos.y).epsilon(eps));

    SECTION("Test aucune connexion")
    {
        REQUIRE(bat.getSortie() == nullptr);

        REQUIRE(bat.getConnexion(static_cast<Vector2i>(vectPos)) == nullptr);
        REQUIRE(bat.getConnexion(Nord) == nullptr);
        REQUIRE(bat.getConnexion(NordOuest) == nullptr);
        REQUIRE(bat.getConnexion(SudOuest) == nullptr);
        REQUIRE(bat.getConnexion(Sud) == nullptr);
        REQUIRE(bat.getConnexion(SudEst) == nullptr);
        REQUIRE(bat.getConnexion(NordEst) == nullptr);

        REQUIRE(bat.getConnexion(NULLDIRECTION) == nullptr);
        REQUIRE(bat.getConnexion(NORD) == nullptr);
        REQUIRE(bat.getConnexion(NORDOUEST) == nullptr);
        REQUIRE(bat.getConnexion(SUDOUEST) == nullptr);
        REQUIRE(bat.getConnexion(SUD) == nullptr);
        REQUIRE(bat.getConnexion(SUDEST) == nullptr);
        REQUIRE(bat.getConnexion(NORDEST) == nullptr);
    }
}