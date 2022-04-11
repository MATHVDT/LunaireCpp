#include "Structure.hpp"

uint Structure::_nbStructures = 0;

Structure::Structure(Vector2f pos)
    : _idStructure(_nbStructures++), _position(pos) {}

Structure::~Structure() {}

void Structure::init(){}

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
