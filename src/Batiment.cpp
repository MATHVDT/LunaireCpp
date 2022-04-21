#include "Batiment.hpp"

uint Batiment::_nbBatiments = 0;
uint Batiment::_idMaxBatiments = 0;
const uint Batiment::_tailleStockEntree = 6;
const uint Batiment::_tailleStockSortie = 1;

connexion_t ConnexionNull{}; // Inutile je crois

/**
 * @brief Construct a new Batiment:: Batiment object
 *
 * @param Vector2f - *pos*
 * @param Texture* - *texture*
 */
Batiment::Batiment(const Vector2u &pos, Texture &texture) : Structure(pos, texture), _idBatiment(++_idMaxBatiments) { _nbBatiments++; }

Batiment::~Batiment()
{
    _nbBatiments--;
    // Deconnecte tous les structures
    while (!_listConnexions.empty())
    {
        deconnecterStructure(*_listConnexions.begin());
    }
}

void Batiment::init() {}

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
 * @brief Checke si la connexion est du bon type de structure
 * @todo Changer le type de structure connectable en tuyau seulement
 * @param connexion_t * - *c*
 * @return true
 * @return false
 */
bool Batiment::checkConnexionPossible(connexion_t *c)
{
    return Structure::checkConnexionPossible(c);
    // &&(typeid(c->structure) == typeid(Structure));
}
