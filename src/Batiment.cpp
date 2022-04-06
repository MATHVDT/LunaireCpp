#include "Batiment.hpp"

uint Batiment::_nbBatiments = 0;

Batiment::Batiment(Vector2f pos) : Structure(pos), _idBatiment(_nbBatiments++)
{
}

Batiment::~Batiment()
{
}
