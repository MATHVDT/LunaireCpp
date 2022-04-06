#include "Structure.hpp"

uint Structure::_nbStructures = 0;

Structure::Structure(Vector2f pos)
    : _id(++_nbStructures), _position(pos) {}

Structure::~Structure() {}

/**
 * @brief Dessine le sprite de la structure 
 */
void Structure::dessiner()
{
    float tailleRef = contextGlobal.getTailleReference();
    _sprite->scale(tailleRef, tailleRef);

    contextGlobal.dessinerFenetre(_sprite);
}
