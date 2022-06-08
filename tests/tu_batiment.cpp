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
#include "direction.hpp"
#include "connexion_t.hpp"

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

    REQUIRE(bat->getPosition().x == vectPos.x);
    REQUIRE(bat->getPosition().y == vectPos.y);

    cout << "     avant new Mine 2     " << endl;
    Batiment *bat2 = new Mine{Vector2u(1, 4)};
    cout << "     apres new Mine 2     " << endl;

    REQUIRE(bat2->getNbStructures() == 2);
    REQUIRE(bat2->getNbBatiments() == 2);

    REQUIRE(bat2->getIdStructure() == idMaxStructures + 2);
    REQUIRE(bat2->getIdBatiment() == idMaxBatiments + 2);

    REQUIRE(bat2->getPosition().x == 1);
    REQUIRE(bat2->getPosition().y == 4);

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
        REQUIRE(bat->getNbConnexions() == 0);
        REQUIRE(bat->getNbEntrees() == 0);
        REQUIRE(bat->getASortie() == 0);

        REQUIRE(bat->getConnexionDirection(static_cast<Vector2i>(vectPos)) == nullptr);
        REQUIRE(bat->getConnexionDirection(Nord) == nullptr);
        REQUIRE(bat->getConnexionDirection(NordOuest) == nullptr);
        REQUIRE(bat->getConnexionDirection(SudOuest) == nullptr);
        REQUIRE(bat->getConnexionDirection(Sud) == nullptr);
        REQUIRE(bat->getConnexionDirection(SudEst) == nullptr);
        REQUIRE(bat->getConnexionDirection(NordEst) == nullptr);

        REQUIRE(bat->getConnexionDirection(NULLDIRECTION) == nullptr);
        REQUIRE(bat->getConnexionDirection(NORD) == nullptr);
        REQUIRE(bat->getConnexionDirection(NORDOUEST) == nullptr);
        REQUIRE(bat->getConnexionDirection(SUDOUEST) == nullptr);
        REQUIRE(bat->getConnexionDirection(SUD) == nullptr);
        REQUIRE(bat->getConnexionDirection(SUDEST) == nullptr);
        REQUIRE(bat->getConnexionDirection(NORDEST) == nullptr);

        REQUIRE(bat->getStructuresConnecteesEntrantes() == list<connexion_t *>{});
        REQUIRE(bat->getStructuresConnectees() == list<connexion_t *>{});
        REQUIRE(bat->getStructuresConnecteesSortante() == nullptr);
    }

    Batiment *bat2 = new Mine{Vector2u(1, 1)};
    connexion_t *c = new connexion_t{bat2, SudEst, false};

    SECTION("Test ajout batiment : 1 connexion")
    {
        REQUIRE(bat->ajouterConnexion(c));

        REQUIRE(bat->getNbConnexions() == 1);
        REQUIRE(bat->getNbEntrees() == 1);
        REQUIRE(bat->getASortie() == 0);

        REQUIRE(bat->getConnexionDirection(Nord) == nullptr);
        REQUIRE(bat->getConnexionDirection(SudEst) == c);
    }

    SECTION("Test ajout batiment : 2 fois la même connexion")
    {
        REQUIRE(bat->ajouterConnexion(c));
        REQUIRE_FALSE(bat->ajouterConnexion(c));

        REQUIRE(bat->getNbConnexions() == 1);
        REQUIRE(bat->getNbEntrees() == 1);
        REQUIRE(bat->getASortie() == false);

        REQUIRE(bat->getConnexionDirection(Nord) == nullptr);
        REQUIRE(bat->getConnexionDirection(SudEst) == c);
    }

    SECTION("Test ajout batiment : sortie")
    {
        c->sortie = true;
        REQUIRE(bat->ajouterConnexion(c));
        REQUIRE_FALSE(bat->ajouterConnexion(c));

        REQUIRE(bat->getNbConnexions() == 1);
        REQUIRE(bat->getNbEntrees() == 0);
        REQUIRE(bat->getASortie() == true);

        REQUIRE(bat->getConnexionDirection(Nord) == nullptr);
        REQUIRE(bat->getConnexionDirection(SudEst) == c);
        REQUIRE(bat->getStructuresConnecteesSortante() == c);
    }

    SECTION("Test ajout batiment : bat2 connecté  verif")
    {
        connexion_t *cInverse = new connexion_t{bat, directionOpposee(c->direction), !c->sortie};

        REQUIRE(bat->ajouterConnexion(c));

        REQUIRE(bat2->getNbConnexions() == 1);
        REQUIRE(bat2->getNbEntrees() == 0);
        REQUIRE(bat2->getASortie() == true);

        REQUIRE(bat2->getConnexionDirection(Nord) == nullptr);
        REQUIRE(bat2->getConnexionDirection(NordOuest)->structure == cInverse->structure);
        REQUIRE(bat2->getConnexionDirection(NordOuest)->direction == cInverse->direction);
        REQUIRE(bat2->getConnexionDirection(NordOuest)->sortie == cInverse->sortie);

        REQUIRE(bat2->getStructuresConnecteesSortante()->structure == cInverse->structure);
        REQUIRE(bat2->getStructuresConnecteesSortante()->direction == cInverse->direction);
        REQUIRE(bat2->getStructuresConnecteesSortante()->sortie == cInverse->sortie);

        delete cInverse;
    }

    SECTION("Test ajout batiment : bat2 connecté sortie verif")
    {
        c->sortie = true;
        connexion_t *cInverse = new connexion_t{bat, directionOpposee(c->direction), !c->sortie};

        REQUIRE(bat->ajouterConnexion(c));

        REQUIRE(bat2->getNbConnexions() == 1);
        REQUIRE(bat2->getNbEntrees() == 1);
        REQUIRE(bat2->getASortie() == false);

        REQUIRE(bat2->getConnexionDirection(Nord) == nullptr);
        REQUIRE(bat2->getConnexionDirection(NordOuest)->structure == cInverse->structure);
        REQUIRE(bat2->getConnexionDirection(NordOuest)->direction == cInverse->direction);
        REQUIRE(bat2->getConnexionDirection(NordOuest)->sortie == cInverse->sortie);
        REQUIRE(bat2->getStructuresConnecteesSortante() == nullptr);

        delete cInverse;
    }

    delete bat;
    delete bat2;
    Mine::dechargerMemoireMines();
}
