/**
 * @file tu_carte->cpp
 * @brief
 */
#include "../include/catch.hpp"
#include "../include/Carte.hpp"

#include <../include/SFML/System/Vector2.hpp>
#include <../include/SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;
using namespace sf;

TEST_CASE("Initialisation de la carte")
{
    RenderWindow window;
    stringstream ss;
    Vector2u coordCase;

    Carte *carte = Carte::getInstance();

    SECTION("Test création objet")
    {
        REQUIRE(carte->getDimensionGrille() == Vector2u(0, 0));
    }

    SECTION("Initialisation grille")
    {
        uint Nlignes = 10;
        uint Ncolonnes = 10;
        // Pour la comparaison
        stringstream ssCaseRef;
        stringstream ssCoordRef;

        for (uint i = 0; i < 2 * Nlignes; ++i)
        {
            if (i % 2 == 0)
            { // Décalage hexagonale
                ssCoordRef << " ";
                ssCaseRef << " ";
            }

            for (uint j = 0; j < Ncolonnes; ++j)
            {
                coordCase = carte->getCoordCase(i, j);
                ssCoordRef << "(" << coordCase.x << "," << coordCase.y << ") ";
                ssCaseRef << 0 << " ";
            }
            ssCoordRef << endl;
            ssCaseRef << endl;
        }

        carte->initCarte(window, Nlignes, Ncolonnes); // Initialisation

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
        carte->initCarte(window, 10, 8);
        carte->initCarte(window, 5, 48);

        uint Nlignes = 10;
        uint Ncolonnes = 10;
        // Pour la comparaison
        stringstream ssCaseRef;
        stringstream ssCoordRef;

        for (uint i = 0; i < 2 * Nlignes; ++i)
        {
            if (i % 2 == 0)
            { // Décalage hexagonale
                ssCoordRef << " ";
                ssCaseRef << " ";
            }
            for (uint j = 0; j < Ncolonnes; ++j)
            {
                coordCase = carte->getCoordCase(i, j);
                ssCoordRef << "(" << coordCase.x << "," << coordCase.y << ") ";
                ssCaseRef << 0 << " ";
            }
            ssCoordRef << endl;
            ssCaseRef << endl;
        }

        // Vérifiaction de la bonne Initialisation
        carte->initCarte(window, Nlignes, Ncolonnes);
        REQUIRE(carte->getDimensionGrille() == Vector2u(Ncolonnes, 2 * Nlignes));
        REQUIRE(carte->getDimensionGrille().x == Vector2u(Ncolonnes, 2 * Nlignes).x);
        REQUIRE(carte->getDimensionGrille().y == Vector2u(Ncolonnes, 2 * Nlignes).y);

        stringstream ssCase;
        carte->afficherConsole(ssCase);

        stringstream ssCoord;
        carte->afficherConsole(ssCoord, true);

        REQUIRE(ssCase.str() == ssCaseRef.str());
        REQUIRE(ssCoord.str() == ssCoordRef.str());
    }
    delete carte;
}
