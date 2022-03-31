/**
 * @file tu_carte->cpp
 * @brief
 */
#include "catch.hpp"
#include "Carte.hpp"

#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

TEST_CASE("Initialisation de la carte")
{
    stringstream ss;

    Carte *carte = Carte::getInstance();

    SECTION("Test création objet")
    {
        REQUIRE(carte->getDimensionGrille() == 0);
    }

    SECTION("Initialisation grille")
    {
        int N = 10;
        // Pour la comparaison
        stringstream ssCaseRef;
        stringstream ssCoordRef;

        for (int i = 0; i < N; ++i)
        {
            if (i % 2 == 0)
            { // Décalage hexagonale
                ssCoordRef << " ";
                ssCaseRef << " ";
            }

            for (int j = 0; j < N; ++j)
            {
                ssCoordRef << "(" << j << "," << i << ") ";
                ssCaseRef << 0 << " ";
            }
            ssCoordRef << endl;
            ssCaseRef << endl;
        }

        carte->initCarte(N); // Initialisation

        stringstream ssCase;
        stringstream ssCoord;

        carte->afficherConsole(ssCase);
        carte->afficherConsole(ssCoord, true);

        REQUIRE(ssCase.str() == ssCaseRef.str());
        REQUIRE(ssCoord.str() == ssCoordRef.str());
    }

    SECTION("Plusieurs init de la grille")
    {
        // Initialisation quelconque
        carte->initCarte(5);
        carte->initCarte(25);

        int N = 10;
        // Pour la comparaison
        stringstream ssCaseRef;
        stringstream ssCoordRef;

        for (int i = 0; i < N; ++i)
        {
            if (i % 2 == 0)
            { // Décalage hexagonale
                ssCoordRef << " ";
                ssCaseRef << " ";
            }
            for (int j = 0; j < N; ++j)
            {
                ssCoordRef << "(" << j << "," << i << ") ";
                ssCaseRef << 0 << " ";
            }
            ssCoordRef << endl;
            ssCaseRef << endl;
        }

        // Vérifiaction de la bonne Initialisation
        carte->initCarte(N);

        stringstream ssCase;
        carte->afficherConsole(ssCase);

        stringstream ssCoord;
        carte->afficherConsole(ssCoord, true);

        REQUIRE(ssCase.str() == ssCaseRef.str());
        REQUIRE(ssCoord.str() == ssCoordRef.str());
    }
    // delete Carte::getInstance();
    delete carte;
}
