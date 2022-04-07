#include "Batiment.hpp"

uint Batiment::_nbBatiments = 0;

Batiment::Batiment(Vector2f pos) : Structure(pos), _idBatiment(_nbBatiments++), _connexion(), _sortie(nullptr), _nbConnexions(), _listConnexions()
{ // Correspond aux Structures connecté au batiment
    for (int i = 0; i < 6; ++i)
    { // Aucune à la création
        _connexion[i] == nullptr;
    }
}

Batiment::~Batiment() {}

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
        if (_connexion[i] == structure)
        {
            _connexion[i] = nullptr;
            _nbConnexions--;
            if (_sortie == structure)
            {
                setSortie(nullptr);
            }
        }
    }
}

/**
 * @brief Donne une liste des *Structures* en entrée sur le Batiment, aucune indication sur la direction des connexions
 * @return list<Structure *> - *listEntrees*
 */
list<Structure *> Batiment::getEntrees() const
{
    list<Structure *> listEntrees;
    listEntrees.remove(_sortie);
    return listEntrees;
}

list<Structure *> Batiment::getConnexionDirection() const
{
    list<Structure *> listConnexions;
    for (int i = 0; i < 6; ++i)
    {
        if (_connexion[i] == nullptr)
        {
            listConnexions.push_back(_connexion[i]);
        }
    }
    return listConnexions;
}
