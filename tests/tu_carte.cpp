/**
 * @file tu_carte.cpp
 * @brief
 */
#include <iostream>
#include <sstream>
#include <cstring>

#include "catch.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include "Carte.hpp"
#include "CaseMap.hpp"
#include "ContextGlobal.hpp"

using namespace std;
using namespace sf;

TEST_CASE("Initialisation de la carte")
{
    stringstream ss;
    Vector2u coordCase;
    CaseMap::chargerSprites("ressource/cheminTexturesCases.txt");

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

            for (uint j = 0; j < Ncolonnes / 2; ++j)
            {
                coordCase = carte->getCoordCase(i, j);
                ssCoordRef << "(" << coordCase.x << "," << coordCase.y << ") ";
                ssCaseRef << 0 << " ";
            }
            ssCoordRef << endl;
            ssCaseRef << endl;
        }

        carte->initCarte(Nlignes, Ncolonnes); // Initialisation

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
        carte->initCarte(10, 8);
        carte->initCarte(5, 48);

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
            for (uint j = 0; j < Ncolonnes / 2; ++j)
            {
                coordCase = carte->getCoordCase(i, j);
                ssCoordRef << "(" << coordCase.x << "," << coordCase.y << ") ";
                ssCaseRef << 0 << " ";
            }
            ssCoordRef << endl;
            ssCaseRef << endl;
        }

        // Vérifiaction de la bonne Initialisation
        carte->initCarte(Nlignes, Ncolonnes);
        REQUIRE(carte->getDimensionGrille() == Vector2u(Ncolonnes / 2, 2 * Nlignes));
        REQUIRE(carte->getDimensionCarte() == Vector2u(Ncolonnes, Nlignes));

        stringstream ssCase;
        carte->afficherConsole(ssCase);

        stringstream ssCoord;
        carte->afficherConsole(ssCoord, true);

        REQUIRE(ssCase.str() == ssCaseRef.str());
        REQUIRE(ssCoord.str() == ssCoordRef.str());
    }
    delete carte;
    CaseMap::dechargerSprites();
}

TEST_CASE("Convertisseur coordonnées")
{

    SECTION("matriceToCarte")
    {
        REQUIRE(Carte::matriceToCarte(Vector2u(0, 0)) == Vector2u(1, 0));
        REQUIRE(Carte::matriceToCarte(Vector2u(2, 2)) == Vector2u(5, 1));
        REQUIRE(Carte::matriceToCarte(Vector2u(3, 4)) == Vector2u(7, 2));
        REQUIRE(Carte::matriceToCarte(Vector2u(4, 3)) == Vector2u(8, 1));
        REQUIRE(Carte::matriceToCarte(Vector2u(5, 5)) == Vector2u(10, 2));
    }

    SECTION("carteToMatrice")
    {
        REQUIRE(Carte::carteToMatrice(Vector2u(0, 0)) == Vector2u(0, 1));
        REQUIRE(Carte::carteToMatrice(Vector2u(2, 2)) == Vector2u(1, 5));
        REQUIRE(Carte::carteToMatrice(Vector2u(3, 4)) == Vector2u(1, 8));
        REQUIRE(Carte::carteToMatrice(Vector2u(4, 3)) == Vector2u(2, 7));
        REQUIRE(Carte::carteToMatrice(Vector2u(5, 5)) == Vector2u(2, 10));
    }
}