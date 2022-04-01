#include "Case.hpp"

float Case::_coteHexagoneRayon = 10.f;
int Case::_nb = 0;

Case::Case(Vector2f pos) : _position{pos}, _typeSol(SOL::Vierge), _hexagone{_coteHexagoneRayon, 6}, _id(_nb)
{
    _hexagone.setOrigin((float)(sqrt(3) / 2) * _coteHexagoneRayon, _coteHexagoneRayon / 2);
    _hexagone.setOrigin(0.f,_coteHexagoneRayon);
    _hexagone.setPosition(_position);

    _hexagone.setRotation(90.f);
    switch (_nb / 6)
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
    _nb++;
    // cout << Case::_nb++ << endl; // temp pour compter les lignes
}

Case::~Case() {}

void Case::afficherConsole(ostream &flux)
{
    flux << static_cast<int>(_typeSol);
}

void Case::afficher(RenderWindow &window)
{
    window.draw(_hexagone);
}

/**
 * @brief Init une case
 *
 * @param Vector2f - *position*
 * @param SOL - *typeSol*
 */
void Case::setCase(Vector2f position,
                   SOL typeSol)
{
    this->setPosition(position);
    this->setTypeSol(typeSol);
}