/**
 * @file Carte.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implémentation de la classe Carte
 * @version 0.1
 * @date 2022-03-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Carte.hpp"

Carte *Carte::_singleton = nullptr;

/**
 * @brief Récupère ou crée un instance de manager *(patron de singleton)*
 * @warning Penser à delete le singleton
 * @return Carte* - *_singleton*
 */
Carte *Carte::getInstance()
{
    // Pas d'instance créée => alors création
    if (Carte::_singleton == nullptr)
        _singleton = new Carte{};
    return _singleton;
}

/**
 * @brief Constructeur d'une carte, ne crée pas de grille
 *
 */
Carte::Carte() : _dimensionGrille(0), _grille(nullptr) {}

/**
 * @brief Destructeur de la carte *(Libère la mémoire associée à la grille)*
 */
Carte::~Carte()
{
    deleteGrille();
    _singleton = nullptr;
}

/**
 * @brief Libère la mémoire associée à la grille
 */
void Carte::deleteGrille()
{
    try
    {
        for (int k = 0; k < _dimensionGrille; ++k)
            delete[] _grille[k];
        delete[] _grille;
        _grille = nullptr;
    }
    catch (const exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

/**
 * @brief Initialise la grille de la Carte suivant une certaine taille
 *
 * @param int - *taille*
 */
void Carte::initCarte(int taille)
{
    // Supprime la grille si elle est déjà existante
    deleteGrille();

    _dimensionGrille = taille;
    _grille = new Case *[_dimensionGrille];
    for (int i = 0; i < _dimensionGrille; ++i)
    {
        _grille[i] = new Case[_dimensionGrille];
        for (int j = 0; j < _dimensionGrille; ++j)
        {
            _grille[i][j].setPosition(j, i); // Valeur par défaut de la case
        }
    }
}

/**
 * @brief Affichage dans un flux la grille
 *
 * @details Affichage des coordonnées des cases si le champ coord est mis à *true*, sinon affichage des cases normales
 *
 * @param ostream & - *flux*
 * @param bool - *coord*
 */
void Carte::afficherConsole(ostream &flux, bool coord)
{
    for (int i = 0; i < _dimensionGrille; ++i)
    {
        if (i % 2 == 0)
            flux << " "; // Décalage hexagonale

        for (int j = 0; j < _dimensionGrille; ++j)
        {
            if (coord)
            {
                flux << "(" << j << "," << i << ") ";
            }
            else
            {
                _grille[i][j].afficherConsole(flux);
                flux << " ";
            }
        }
        flux << endl;
    }
}

void Carte::afficher(RenderWindow &window)
{
    float tailleCase = Case::getTailleCase();
    Vector2f positionEcran{0, 0};
    for (int y = 0; y < _dimensionGrille; ++y)
    {
        if (y % 2 == 0) // Décalage hexagonale
            positionEcran.x += 1.5f * tailleCase;

        for (int x = 0; x < _dimensionGrille; ++x)
        {
            cout << positionEcran.x << ", " << positionEcran.y << endl;
            _grille[y][x].afficher(window, positionEcran);
            positionEcran.x += 1.5f * tailleCase;
        }
        // (sqrt(3) / 2) *
        positionEcran.y += tailleCase;
        positionEcran.x = 0;
    }
}