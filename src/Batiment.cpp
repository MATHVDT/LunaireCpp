#include "Batiment.hpp"

uint Batiment::_nbBatiments = 0;

Batiment::Batiment(Vector2f pos) : Structure(pos), _idBatiment(_nbBatiments++)
{
    for (int i = 0; i < 6; ++i)
    {
        _voisinage[i] == nullptr;
    }
}

Batiment::~Batiment()
{
}
