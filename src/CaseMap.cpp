#include "CaseMap.hpp"

float CaseMap::_coteHexagoneRayon = 10.f;
float CaseMap::_tailleCaseMap = 0.f;
float CaseMap::_scaleCaseMap = 0.f;
uint CaseMap::_tailleTexture = 0;

int CaseMap::_nb = 0;
Texture *CaseMap::_texturesSol[5];

/**
 * @brief Constructeur de case
 * @warning CaseMap vierge il faut faire setCase après pour définir ses paramètres
 * @param Vector2f - *posistion = défaut Vector2f{0, 0}*
 */
CaseMap::CaseMap(Vector2f pos) : _id(_nb++), _position{pos}, _typeSol(SOL::Vierge), _sprite(new Sprite)
{
    // set du sol et donc du sprite aussi
    setCase(_position, _typeSol);
}

/**
 * @brief Destructeur CaseMap
 *
 */
CaseMap::~CaseMap() { delete _sprite; }

void CaseMap::afficherConsole(ostream &flux)
{
    flux << static_cast<int>(_typeSol);
}

/**
 * @brief Affiche une case et ce qui la compose à l'écran
 *
 * @param RenderWindow & - *window*
 */
void CaseMap::dessiner()
{
    // cout << _sprite->getTexture()->getSize().y
    //      << " (" << _position.x << "," << _position.y << ")";
    // cout << " tailleCaseMap : " << _tailleCaseMap;
    // cout << " scaleCaseMap : " << _scaleCaseMape << endl;

    _sprite->setScale(_scaleCaseMap, _scaleCaseMap);
    contextGlobal.dessinerFenetre(_sprite);

    // Texte a afficher
    /*
        // Font font;
        // Text text;

        // font.loadFromFile("ressource/fonts/arial.ttf");
        // text.setFont(font);
        // // text.setString(L"Hé_à_i_ù");
        // text.setString(to_string(_id));
        // Vector2f positionTexte;
        // positionTexte.x = _position.x + _tailleCaseMap / 2.f - text.getCharacterSize() / 2.f;
        // positionTexte.y = _position.y + (_tailleCaseMap - text.getCharacterSize()) / 2.f;
        // text.setOutlineColor(Color::Blue);
        // text.setOutlineThickness(2.f);

        // text.setCharacterSize(20);
        // text.setPosition(positionTexte);

        // window.draw(text);
    */
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
    this->setSpriteTexture(typeSol);
}

/**
 * @brief Défini la taille d'une case => cotés de l'hexagone
 * @warning Semble ne pas être utile car les dimensions sont ajustées en fonction de la taille de la fenêtre
 * @param uint - *nbLignesGrille*
 * @param uint - *nbColonnesGrille*
 */
void CaseMap::setScaleCaseMap(uint nbLignesCarte,
                              uint nbCcolonnesCarte)
{
    const Vector2u dimFenetre = contextGlobal.getDimensionFenetre();
    // uint minEcran = min(dimFenetre.x, dimFenetre.y);
    // uint maxCases = max(nbLignesCarte, nbCcolonnesCarte);

    float scaleX =
        (float)dimFenetre.x / ((float)nbCcolonnesCarte + 1.f) / _tailleTexture;
    float scaleY =
        (float)dimFenetre.y / ((float)nbLignesCarte + 0.5f) / _tailleTexture;

    _scaleCaseMap = min(scaleX, scaleY);
    _tailleCaseMap = (float)_tailleTexture * _scaleCaseMap;
    contextGlobal.setTailleReference(_tailleCaseMap);
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
        _tailleTexture = texture->getSize().y;
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
