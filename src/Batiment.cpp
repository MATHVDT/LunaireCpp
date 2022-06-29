/**
 * @file Batiment.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implémentation des méthodes de la classe Batiment
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 */
#include "Batiment.hpp"

uint Batiment::_nbBatiments = 0;
uint Batiment::_idMaxBatiments = 0;

const uint Batiment::_tailleStockEntree = 6;
const uint Batiment::_tailleStockSortie = 1;

Batiment::Batiment()
    : _idBatiment(++_idMaxBatiments)
{
    _nbBatiments++;
    cerr << "Batiment() = default, id : " << _idBatiment << endl;
}

/**
 * @brief Construct a new Batiment:: Batiment object
 *
 * @param Vector2f - *pos*
 * @param Texture* - *texture*
 */
Batiment::Batiment(const Vector2u &pos,
                   Texture *text,
                   uint tailleStockEntree,
                   uint tailleStockSortie)
    : Structure{pos, text,
                tailleStockEntree, tailleStockSortie},
      _idBatiment(++_idMaxBatiments)
{
    _nbBatiments++;
    cerr << "Batiment(), id : " << _idBatiment << endl;
}

Batiment::~Batiment()
{
    _nbBatiments--;
    cerr << "~Batiment(), id : " << _idBatiment << endl;
}

void Batiment::init() {}

/*******************************************************/

void Batiment::chargerMemoireBatiments()
{
    // Mine::chargerMemoireMines();
    // chargerMemoire Autres Batiment
}

void Batiment::dechargerMemoireBatiments()
{
    // Mine::dechargerMemoireMines();
    // dechargerMemoire Autres Batiment
}

/*******************************************************/

void Batiment::dessiner(float scaleSprite)
{
    Structure::dessiner(scaleSprite);
}

void Batiment::update()
{
    Structure::update();
}

void Batiment::process() {}

/*******************************************************/

/**
 * @brief Check si la connexion entre le Batiment et une autre strucutre est possible (nb de connexion)
 *
 * @details Dans la méthode override, on regarde si la structrures peut avoir une connexion suplémentaire (sortie ou entrée). Puis dans la méthode Structure::checkConnexionPossible, on regarde si c'est la structure que l'on veut ajouter qui peut accepeter une connexion supplémentaire (entrée ou sortie).
 *
 * @param Structure * - *s*
 * @param bool - *commeSortie*
 *
 * @return true - *Connexion possible*
 * @return false - *Connexion impossible*
 */
bool Batiment::checkConnexionPossible(Structure *s, bool commeSortie)
{
    // Vérifie le nombre d'entrées
    if (commeSortie)
    {
        // Faut que la structure a co ait des entrées libres
        if (s->getNbEntrees() >= s->getTailleStockEntree())
            return false; // Toutes les entrées prises
    }
    else // !commeSortie
    {
        // Faut que this ait des entrées de libres
        if (this->getNbEntrees() >= this->getTailleStockEntree())
            return false; // Toutes les entrées prises
    }

    // Vérifier la compatibilité des structures connectées
    if (typeid(*s) != typeid(Pipeline))
    {
        cout << "Pas un pipeline que l'on co a ce batiement" << endl;
        return false; // Co à autre chose que pipeline
    }
    return Structure::checkConnexionPossible(s, commeSortie);
}

bool Batiment::updateOrientation()
{
    // Rien
    return false;
}
