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

/**
 * @brief Constructeur d'une carte, ne crée pas de grille
 *
 */
Carte::Carte() : _dimensionGrille(0), _grille(nullptr) {}

/**
 * @brief Destructeur de la carte *(Libère la mémoire associée à la grille)*
 */
Carte::~Carte() { deleteGrille(); }

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
    _grille = new int *[_dimensionGrille];
    for (int i = 0; i < _dimensionGrille; ++i)
    {
        _grille[i] = new int[_dimensionGrille];
        for (int j = 0; j < _dimensionGrille; ++j)
        {
            _grille[i][j] = 0; // Valeur par défaut de la case
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
        if (i % 2 == 1)
            flux << " "; // Décalage hexagonale

        for (int j = 0; j < _dimensionGrille; ++j)
        {
            if (coord)
                flux << "(" << j << "," << i << ") ";
            else
                flux << _grille[i][j] << " ";
        }
        flux << endl;
    }
}
