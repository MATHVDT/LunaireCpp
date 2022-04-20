#include "Structure.hpp"

uint Structure::_nbStructures = 0;
uint Structure::_idMaxStructures = 0;

Structure::Structure(Vector2u pos, Texture *text)
    : _idStructure(++_idMaxStructures), _position(pos), _sprite(new Sprite(*text))
{
    _nbStructures++;
    Vector2f posEcran = Carte::carteToPositionEcran(_position);
    _sprite->setPosition(posEcran);
}

Structure::~Structure() { _nbStructures--; }

void  Structure::init(){}

/**
 * @brief Charge la mémoire allouée aux structures
 * (textures ...)
 */
void Structure::chargerMemoireStructures()
{
    // Batiment::chargerMemoireBatiments();
}

/**
 * @brief Libère la mémoire allouée aux structures
 * (textures ...)
 */
void Structure::dechargerMemoireStructures()
{
    // Batiment::dechargerMemoireBatiments();
}

/**
 * @brief Dessine le sprite de la structure à la bonne taille
 * @details *ObjetFille::dessiner()* doit calculer le scale pour adapté le sprite, et appelé cette méthode pour dessiner le sprite dans la fenêtre au bonne dimension
 * @param float - *scaleSprite*
 */
void Structure::dessiner(float scaleSprite)
{
    _sprite->scale(scaleSprite, scaleSprite);
    contextGlobal.dessinerFenetre(_sprite);
}

void Structure::update()
{
    // Récupérer les ressources des entrées
    remplirStock();

    // Traiter les ressources
    // ... ^ v
    // Mettre les ressources à la sortie
}
