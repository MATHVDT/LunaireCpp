#include "Case.hpp"

float Case::_coteHexagoneRayon = 500.f;

Case::Case(float x, float y) : _position{x, y}, _etat(0) {}

Case::~Case()
{
}

void Case::afficherConsole(ostream &flux)
{
    flux << _etat;
}

void Case::afficher(RenderWindow &window, Vector2f positionEcran)
{
    CircleShape shape{_coteHexagoneRayon, 6};
    shape.setPosition(positionEcran);
    shape.setFillColor(sf::Color{rand()%255,rand()%255,rand()%255});
    window.draw(shape);
}
