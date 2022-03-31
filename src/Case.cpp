#include "Case.hpp"

float Case::_coteHexagoneRayon = 10.f;
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

void Case::afficher(RenderWindow &window)
{
    window.draw(_hexagone);
}
