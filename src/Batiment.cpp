#include "Batiment.hpp"

uint Batiment::_nbBatiments = 0;

Batiment::Batiment(Vector2f pos) : Structure(pos), _idBatiment(_nbBatiments++), _voisinage(), _sortie(nullptr)
{ // Correspond aux Structures connecté au batiment
    for (int i = 0; i < 6; ++i)
    { // Aucune à la création
        _voisinage[i] == nullptr;
    }
}

Batiment::~Batiment()
{
}

/**
 * @brief Defini une structure de sortie sur le batiment
 * @details Chaque batiment ne peut avoir qu'une structure de sortie
 * @param Structure * - *structure*
 */
void Batiment::setSortie(Structure *structure)
{
    _sortie = structure;
}
void Batiment::init() {}

void Batiment::dessiner(float scaleSprite) {}

void Batiment::update() {}


/**
 * @brief Déconnecte une structure du batiment
 *
 * @param Structure * - *structure*
 */
void Batiment::deconnecterStructure(Structure *structure)
{
    for (int i = 0; i < 6; ++i)
    {
        if (_voisinage[i] == structure)
        {
            _voisinage[i] = nullptr;
            if (_sortie == structure)
            {
                setSortie(nullptr);
            }
        }
    }
}
