#include "CaseMap.hpp"

float CaseMap::_coteHexagoneRayon = 10.f;
float CaseMap::_coteCaseMap = 5.f;

int CaseMap::_nb = 0;
Texture *CaseMap::_texturesSol[5];

CaseMap::CaseMap(Vector2f pos) : _position{pos}, _typeSol(SOL::Vierge), _hexagone{_coteHexagoneRayon, 6}, _id(_nb), _sprite(new Sprite)
{
    // set du sol et donc du sprite aussi
    setTypeSol(SOL::Vierge);
    setSprite();

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

CaseMap::~CaseMap() { delete _sprite; }

void CaseMap::afficherConsole(ostream &flux)
{
    flux << static_cast<int>(_typeSol);
}

void CaseMap::afficher(RenderWindow &window)
{
    window.draw(*_sprite);
}

/**
 * @brief Init une case
 *
 * @param Vector2f - *position*
 * @param SOL - *typeSol*
 */
void CaseMap::setCase(Vector2f position,
                   SOL typeSol)
{
    this->setPosition(position);
    this->setTypeSol(typeSol);
}

/**
 * @brief Défini la taille d'une case => cotés de l'hexagone
 * @warning Semble ne pas être utile car les dimensions sont ajustées en fonction de la taille de la fenêtre
 * @param RenderWindow & - *window*
 * @param uint - *nbLignesGrille*
 * @param uint - *nbColonnesGrille*
 */
void CaseMap::setTailleCase(RenderWindow &window,
                         uint nbLignesGrille,
                         uint nbCcolonnesGrille)
{
    uint minEcran = min(window.getSize().x, window.getSize().y);
    uint maxCases = max(nbLignesGrille, nbCcolonnesGrille);

    float largeurTexture = (float)_texturesSol[0]->getSize().x;
    cout << "taille texture : " << largeurTexture << endl;

    _coteHexagoneRayon = (float)window.getSize().y / ((float)nbLignesGrille + 0.5f) / largeurTexture;
}

/**
 * @brief Charge les différents sprites des cases
 * @details
 * Charge depuis le fichier les différents chemins de différentes textures des cases, et charge ensuite les textures dans des sprites associés au tableau contenant les différents sprites des cases
 * @param string - *fichierCheminsTexture*
 */
void CaseMap::chargerSprites(string fichierCheminsTexture)
{
    string nomFichierTexture[5];
    string cheminTexture;
    sf::Texture *texture;

    std::ifstream monFlux;
    monFlux.open(fichierCheminsTexture);

    if (monFlux)
    {
        // Récupération des chemins
        for (int k = 0; k < 5; ++k) // 5 defini en dur !
        {
            monFlux >> cheminTexture;

            // Declare and load a texture

            // Create a new sprite
            texture = new Texture();
            texture->loadFromFile(cheminTexture);

            _texturesSol[k] = texture;
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
void CaseMap::dechargerSprites()
{
    for (int k = 0; k < 5; ++k) // 5 defini en dur !
    {
        delete _texturesSol[k];
    }
}
