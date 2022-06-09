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

connexion_t ConnexionNull{}; // Inutile je crois

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
 * @brief Check si la connexion entre les 2 Structures est possible, et si la structure peut être connectée au batiment
 * @todo Vérfier si la structure peut être connectée
 *
 * @param Structure * - *s*
 * @return true - *Connexion possible*
 * @return false - *Connexion impossible*
 */
bool Batiment::checkConnexionPossible(Structure *s)
{
    return Structure::checkConnexionPossible(s);
    // &&(typeid(c->structure) == typeid(Structure));
}
