#include "Case.hpp"

float Case::_coteHexagoneRayon = 10.f;
int Case::_nb = 0;
Sprite *Case::_spritesSol[5];

Case::Case(Vector2f pos) : _position{pos}, _typeSol(SOL::Vierge), _hexagone{_coteHexagoneRayon, 6}, _id(_nb), _sprite(nullptr)
{
    _hexagone.setPosition(_position);
    _hexagone.setOrigin(0, 2 * _coteHexagoneRayon);
    _hexagone.setOrigin(0.f, _coteHexagoneRayon);
    if (_id == 1)
    {
        _hexagone.setOutlineColor(Color::Yellow);
        _hexagone.setOutlineThickness(1.f);
    }
    if (_id == 0)
    {
        _hexagone.setOutlineColor(Color::Red);
        _hexagone.setOutlineThickness(1.f);
    }

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

Case::~Case() { _sprite = nullptr; }

void Case::afficherConsole(ostream &flux)
{
    flux << static_cast<int>(_typeSol);
}

void Case::afficher(RenderWindow &window)
{
    window.draw(*_sprite);
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

/**
 * @brief Défini la taille d'une case => cotés de l'hexagone
 * @warning Semble ne pas être utile car les dimensions sont ajustées en fonction de la taille de la fenêtre
 * @param unit - *tailleEcran*
 * @param int - *nbCase*
 */
void Case::setTailleCase(RenderWindow &window,
                         uint nbLignes, uint nbCcolonnes)
{
    // cout << "ecran : " << tailleEcran << ", nb cases : " << nbCase << endl;
    uint minEcran = min(window.getSize().x, window.getSize().y);
    uint maxCases = max(nbLignes, nbCcolonnes);
    // _coteHexagoneRayon = (float)minEcran / ((float)maxCases + 1.5f);
    // cout << "cote : " << _coteHexagoneRayon << endl;
    _coteHexagoneRayon = (float)window.getSize().y / ((float)nbLignes + 2.f) / (float)(sqrt(3) / 2.f);
}

/**
 * @brief Charge les différents sprites des cases
 * @details
 * Charge depuis le fichier les différents chemins de différentes textures des cases, et charge ensuite les textures dans des sprites associés au tableau contenant les différents sprites des cases
 * @param string - *fichierCheminsTexture*
 */
void Case::chargerSprites(string fichierCheminsTexture)
{
    string nomFichierTexture[5];
    string cheminTexture;
    sf::Texture texture;

    Sprite *sprite;

    std::ifstream monFlux;
    monFlux.open(fichierCheminsTexture);

    if (monFlux)
    {
        // Récupération des chemins
        for (int k = 0; k < 5; ++k) // 5 defini en dur !
        {
            monFlux >> cheminTexture;

            // Declare and load a texture
            texture.loadFromFile("texture.png");

            // Create a new sprite
            sprite = new Sprite();
            sprite->setTexture(texture);

            _spritesSol[k] = sprite;
        }

        monFlux.close();
    }
    else
    {
        std::cerr << "/!\\ Erreur d'ouverture du fichier : " << fichierCheminsTexture << " /!\\" << endl;
    }
}

/**
 * @brief Libère la mémoire des sprites de cases chargées
 * @warning Les cases ne doivent plus être utilisées après
 */
void Case::dechargerSprites()
{
    for (int k = 0; k < 5; ++k) // 5 defini en dur !
    {
        delete _spritesSol[k];
    }
}
