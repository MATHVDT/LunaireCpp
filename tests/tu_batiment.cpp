/**
 * @file tu_batiment.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Tests Unitaires de la classe Batiment
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 */
#include <iostream>
#include <sstream>
#include <cstring>
#include <list>

#include "catch.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include "Structure.hpp"
#include "Batiment.hpp"
#include "Mine.hpp"
#include "Pipeline.hpp"
#include "direction.hpp"

using namespace std;
using namespace sf;

TEST_CASE("Test création batiment")
{
    Mine::chargerMemoireMines();

    uint idMaxStructures = Structure::getIdMaxStructures();
    uint idMaxBatiments = Batiment::getIdMaxBatiments();

    float eps = 0.0001;
    Vector2u vectPos{0, 0};
    Batiment *bat = new Mine{Vector2u(vectPos)};

    REQUIRE(bat->getNbStructures() == 1);
    REQUIRE(bat->getNbBatiments() == 1);

    REQUIRE(bat->getIdStructure() == idMaxStructures + 1);
    REQUIRE(bat->getIdBatiment() == idMaxBatiments + 1);

    REQUIRE(bat->getPositionCarte().x == vectPos.x);
    REQUIRE(bat->getPositionCarte().y == vectPos.y);

    cout << "     avant new Mine 2     " << endl;
    Batiment *bat2 = new Mine{Vector2u(1, 4)};
    cout << "     apres new Mine 2     " << endl;

    REQUIRE(bat2->getNbStructures() == 2);
    REQUIRE(bat2->getNbBatiments() == 2);

    REQUIRE(bat2->getIdStructure() == idMaxStructures + 2);
    REQUIRE(bat2->getIdBatiment() == idMaxBatiments + 2);

    REQUIRE(bat2->getPositionCarte().x == 1);
    REQUIRE(bat2->getPositionCarte().y == 4);

    delete bat2;
    delete bat;

    Mine::dechargerMemoireMines();
}

TEST_CASE("Connexion batiment")
{
    Mine::chargerMemoireMines();

    float eps = 0.0001;
    Vector2u vectPos{0, 0};
    Batiment *bat = new Mine{Vector2u(vectPos)};

    SECTION("Test aucune connexion")
    {
        REQUIRE(bat->getNbConnexionsOccupees() == 0);
        REQUIRE(bat->getNbEntrees() == 0);
        REQUIRE(bat->getASortie() == 0);

        REQUIRE(bat->getStructuresConnecteesEntrantes() == list<Structure *>{});
        REQUIRE(bat->getStructuresConnectees() == list<Structure *>{});
        REQUIRE(bat->getSortie() == nullptr);
    }

    Pipeline *p = new Pipeline{Vector2u(1, 1)};

    SECTION("Test ajout batiment en sortie")
    {
        REQUIRE(bat->connecterStructure(p, true));

        REQUIRE(bat->getNbConnexionsOccupees() == 1);
        REQUIRE(bat->getNbEntrees() == 0);
        REQUIRE(bat->getASortie() == true);
        REQUIRE(bat->getSortie() == p);
    }

    SECTION("Test ajout batiment 2 fois la même connexion en sortie")
    {
        REQUIRE(bat->connecterStructure(p, true));
        REQUIRE_FALSE(bat->connecterStructure(p, true));

        REQUIRE(bat->getNbConnexionsOccupees() == 1);
        REQUIRE(bat->getNbEntrees() == 0);
        REQUIRE(bat->getASortie() == true);
        REQUIRE(bat->getSortie() == p);
    }

    SECTION("Test ajout batiment  en entrée")
    {
        REQUIRE(bat->connecterStructure(p, false));

        REQUIRE(bat->getNbConnexionsOccupees() == 1);
        REQUIRE(bat->getNbEntrees() == 1);
        REQUIRE(bat->getASortie() == false);
        REQUIRE(bat->getSortie() == nullptr);
    }

    SECTION("Test ajout batiment 2 fois la même connexion en entrée")
    {
        REQUIRE(bat->connecterStructure(p, false));
        REQUIRE_FALSE(bat->connecterStructure(p, false));

        REQUIRE(bat->getNbConnexionsOccupees() == 1);
        REQUIRE(bat->getNbEntrees() == 1);
        REQUIRE(bat->getASortie() == false);
        REQUIRE(bat->getSortie() == nullptr);
    }

    SECTION("Test ajout batiment 2 fois la même connexion en entrée puis en entrée")
    {
        REQUIRE(bat->connecterStructure(p, false));
        REQUIRE_FALSE(bat->connecterStructure(p, true));

        REQUIRE(bat->getNbConnexionsOccupees() == 1);
        REQUIRE(bat->getNbEntrees() == 1);
        REQUIRE(bat->getASortie() == false);
        REQUIRE(bat->getSortie() == nullptr);
    }

    SECTION("Test ajout batiment 2 fois la même connexion en entrée puis en sortie puis en entrée")
    {
        REQUIRE(bat->connecterStructure(p, true));
        REQUIRE_FALSE(bat->connecterStructure(p, false));

        REQUIRE(bat->getNbConnexionsOccupees() == 1);
        REQUIRE(bat->getNbEntrees() == 0);
        REQUIRE(bat->getASortie() == true);
        REQUIRE(bat->getSortie() == p);
    }

    SECTION("Test ajout de strucutres non autorisé a ce sonnecter à un batiment")
    {
        Mine *bat2 = new Mine{Vector2u(1, 0)};
        Batiment *bat3 = new Mine{Vector2u(1, 0)};
        Structure *bat4 = new Mine{Vector2u(1, 0)};
        
        REQUIRE_FALSE(bat->connecterStructure(bat2, true));
        REQUIRE_FALSE(bat->connecterStructure(bat3, true));
        REQUIRE_FALSE(bat->connecterStructure(bat4, true));

        REQUIRE(bat->getNbConnexionsOccupees() == 0);
        REQUIRE(bat->getNbEntrees() == 0);
        REQUIRE(bat->getASortie() == false);
        REQUIRE(bat->getSortie() == nullptr);

        delete bat2;
        delete bat3;
        delete bat4;
    }

    delete bat;
    delete p;
    Mine::dechargerMemoireMines();
}
