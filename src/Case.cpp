#include "Case.hpp"

float Case::_coteHexagoneRayon = 500.f;
int Case::_nb = 0;

Case::Case(Vector2f pos) : _position{pos}, _etat(0), _hexagone{_coteHexagoneRayon, 6}
{
    _hexagone.setOrigin(0, 2*_coteHexagoneRayon);
    _hexagone.setPosition(_position);
    _hexagone.setRotation(90.f);
    switch (_nb / 4)
    {
    case 0:
        _hexagone.setFillColor(Color::Blue);
        break;
    case 1:
        _hexagone.setFillColor(Color::Red);
        break;
    case 2:
        _hexagone.setFillColor(Color::Yellow);
        break;
    case 3:
        _hexagone.setFillColor(Color::Green);
        break;
    default:
        _hexagone.setFillColor(Color::White);
        break;
    }
    cout << Case::_nb++ << endl; // temp pour compter les lignes
}

Case::~Case() {}

void Case::afficherConsole(ostream &flux)
{
    flux << _etat;
}

void Case::afficher(RenderWindow &window, Vector2f positionEcran)
{
    // CircleShape circle{_coteHexagoneRayon};
    // circle.setPosition(positionEcran);
    // circle.setFillColor(sf::Color::White);
    // // window.draw(circle);

    // CircleShape shape{_coteHexagoneRayon, 6};
    // // shape.setOrigin(_coteHexagoneRayon, _coteHexagoneRayon);
    // shape.setPosition(positionEcran);
    // shape.setRotation(90.f);
    // // shape.setFillColor(sf::Color{((int)_position.x / (int)_coteHexagoneRayon) % 255, ((int)_position.y / (int)_coteHexagoneRayon) % 255, 255});
    // shape.setFillColor(sf::Color{rand() % 255, rand() % 255, rand() % 255});
    // window.draw(shape);

    window.draw(_hexagone);
}
