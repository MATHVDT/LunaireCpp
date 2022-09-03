/**
 * @file CaseMap.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implémentation des méthodes de la classe Carte
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 */
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
CaseMap::CaseMap(Vector2u pos) : _id(_nb++), _position{pos}, _typeSol(TYPE_SOL::Vierge), _sprite(new Sprite), _construction(nullptr)
{
    // set du sol et donc du sprite aussi
    setCase(_position, _typeSol);
}

/**
 * @brief Destructeur CaseMap
 * @todo delete la _constuction sur la carte, a term soit le batiment est supprimé de la case et donc delete, soit lorsque la carte est reset on delete le batiment
 */
CaseMap::~CaseMap()
{
    delete _sprite;
    // delete _construction;
}

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
    contextGlobal->dessinerFenetre(_sprite);

    if (_construction != nullptr)
        _construction->dessiner(_scaleCaseMap);

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
 * @param TYPE_SOL - *typeSol*
 */
void CaseMap::setCase(Vector2u position,
                      TYPE_SOL typeSol)
{
    Vector2f posEcran = Carte::carteToPositionEcran(_position);
    this->setPositionCarte(position);

    this->setTypeSol(typeSol);
    this->setSpriteTexture(typeSol);
}

/**
 * @brief Set la position de la case et la position du sprite sur l'écran
 *
 * @param const Vector2u & - *pos*
 */
void CaseMap::setPositionCarte(const Vector2u &pos)
{
    _position = pos;
    Vector2f coordEcran = Carte::carteToPositionEcran(_position);
    _sprite->setPosition(coordEcran);
}

/**
 * @brief Défini la taille d'une case => cotés de l'hexagone
 * @warning Semble ne pas être utile car les dimensions sont ajustées en fonction de la taille de la fenêtre
 * @param uint - *nbLignesGrille*
 * @param uint - *nbColonnesGrille*
 */
void CaseMap::setScaleCaseMap(uint nbLignesCarte,
                              uint nbColonnesCarte)
{
    const Vector2u dimFenetre = contextGlobal->getDimensionFenetre();
    // uint minEcran = min(dimFenetre.x, dimFenetre.y);
    // uint maxCases = max(nbLignesCarte, nbColonnesCarte);

    float scaleX = contextGlobal->getLargeurMapEcran() / (float)(nbColonnesCarte * (float)3.f * _tailleTexture / 4.f + (float)1.f * _tailleTexture / 4.f);

    float scaleY =
        (float)dimFenetre.y / ((float)nbLignesCarte + 0.5f) / _tailleTexture;

    _scaleCaseMap = min(scaleX, scaleY);
    _tailleCaseMap = (float)_tailleTexture * _scaleCaseMap;
    contextGlobal->setTailleReference(_tailleCaseMap);
    contextGlobal->setScaleReference(_scaleCaseMap);
}

/*******************************************************/
void CaseMap::chargerMemoireCaseMap()
{
    CaseMap::chargerSprites("ressource/cheminTextures/cheminTexturesCases.txt");
}

void CaseMap::dechargerMemoireCaseMap()
{
    CaseMap::dechargerSprites();
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

/*******************************************************/

/**
 * @brief Ajoute une structure si la place sur la case n'est pas déjà occupée.
 *
 * @param Structure * - *s*
 */
void CaseMap::ajouterConstruction(Structure *s)
{
    if (_construction != nullptr)
        return;
    _construction = s;
}
