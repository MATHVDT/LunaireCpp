/**
 * @file Carte.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implémentation de la classe Carte
 * @version 0.1
 * @date 2022-03-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Carte.hpp"

Carte *Carte::_singleton = nullptr;

/**
 * @brief Récupère ou crée un instance de manager *(patron de singleton)*
 * @warning Penser à delete le singleton
 * @return Carte* - *_singleton*
 */
Carte *Carte::getInstance()
{
    // Pas d'instance créée => alors création
    if (Carte::_singleton == nullptr)
        _singleton = new Carte{};
    return _singleton;
}

/**
 * @brief Constructeur d'une carte, ne crée pas de grille
 *
 */
Carte::Carte() : _nbColonnesGrille(0), _nbLignesGrille(0), _grille(nullptr) {}

/**
 * @brief Destructeur de la carte *(Libère la mémoire associée à la grille)*
 */
Carte::~Carte()
{
    deleteGrille();
    _singleton = nullptr;
}

/**
 * @brief Libère la mémoire associée à la grille
 */
void Carte::deleteGrille()
{
    try
    {
        for (uint y = 0; y < _nbLignesGrille; ++y)
        {
            delete[] _grille[y];
        }
        delete[] _grille;
        _grille = nullptr;
        _nbLignesGrille = _nbColonnesGrille = 0;
        _nbLignesCarte = _nbColonnesCarte = 0;
    }
    catch (const exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

/**
 * @brief Alloue les tableaux pour la grille, et set les attributs dimensions
 *
 * @warning L'attribut *_grille* doit être *nullptr*
 *
 * @param uint - *nbLignes*
 * @param uint - *nbColonnes*
 */
void Carte::creerGrille(uint nbLignes, uint nbColonnes)
{
    _nbLignesCarte = nbLignes;
    _nbColonnesCarte = nbColonnes;
    _nbLignesGrille = 2 * _nbLignesCarte;
    _nbColonnesGrille = _nbColonnesCarte / 2;

    _grille = new CaseMap *[_nbLignesGrille];

    for (uint i = 0; i < _nbLignesGrille; ++i)
    {
        _grille[i] = new CaseMap[_nbColonnesGrille];
    }
}

void Carte::initCarte(const string nomFichierMap)
{
    // Supprime la grille si elle est déjà existante
    deleteGrille();
    uint nbLignes, nbColonnes;
    int typeSol;
    ifstream monFlux;
    monFlux.open(nomFichierMap);

    if (monFlux)
    {
        monFlux >> nbLignes;
        monFlux >> nbColonnes;
        creerGrille(nbLignes, nbColonnes);

        for (int i = 0; i < _nbLignesGrille; ++i)
        {
            for (int j = 0; j < _nbColonnesGrille; ++j)
            {
                monFlux >> typeSol;
                _grille[i][j].setTypeSol(static_cast<SOL>(typeSol));
                _grille[i][j].setSpriteTexture(static_cast<SOL>(typeSol));
            }
        }
        setCaseEcran();
        monFlux.close(); // Fermeture du fichier
    }
    else
    {
        std::cerr << "/!\\ Erreur d'ouverture du fichier : " << nomFichierMap << " /!\\" << endl;
    }
}

/**
 * @brief Initialise la grille de la Carte suivant une certaine taille
 * @deprecated Ne pas utiliser, il n'y a pas la boucle de setCase
 * @param uint - *nbLignes*
 * @param uint - *nbColonnes*
 */
void Carte::initCarte(uint nbLignes, uint nbColonnes)
{
    // Supprime la grille si elle est déjà existante
    deleteGrille();
    creerGrille(nbLignes, nbColonnes);
    // ajustageCasesHexagone(window);
}

/**
 * @brief Ajuste la taille des cases en focntion de la taille de la fenêtre
 * @deprecated Plus utilisé car plus de forme dans les cases
 * @param RenderWindow & - *window*
 */
/*
void Carte::ajustageCasesHexagone(RenderWindow &window)
{
    // Recalcule de la taille d'une case
    CaseMap::setScaleCaseMap(window,
                             _nbLignesCarte,
                             _nbColonnesCarte);
    float tailleCase = CaseMap::getScaleCaseMap();
    Vector2f positionEcran{0.f, 0.f};
    Vector2f coordCase{0.f, 0.f};

    for (uint i = 0; i < _nbLignesGrille; i++)
    {
        // Décalage hexagonale une ligne sur deux
        if (i % 2 == 0)
        { // Décalage une demi hauteur d'hexagone
            positionEcran.x = (3.f * tailleCase / 2.05f);
        }
        for (uint j = 0; j < _nbColonnesGrille; ++j)
        {
            // Position de la forme hexagone
            _grille[i][j].setPosition(positionEcran);
            positionEcran.x += 2.f * tailleCase + (tailleCase * 2 / sqrt(3.f));
        }
        positionEcran.y += (sqrt(3) / 2) * tailleCase;
        // positionEcran.y +=  tailleCase;
        positionEcran.x = 0;
    }
}
*/

void Carte::setCaseEcran()
{
    Vector2u coordMatrice;
    Vector2u coordCarte;
    Vector2f coordEcran;

    CaseMap::setScaleCaseMap(_nbLignesCarte,
                             _nbColonnesCarte);

    for (int i = 0; i < _nbLignesGrille; ++i)
    {
        coordMatrice.y = i;
        for (int j = 0; j < _nbColonnesGrille; ++j)
        {
            coordMatrice.x = j;
            coordCarte = matriceToCarte(coordMatrice);
            coordEcran = carteToPositionEcran(coordCarte);
            _grille[i][j].setPosition(coordEcran);
        }
    }
}

/**
 * @brief Affichage dans un flux la grille
 *
 * @details Affichage des coordonnées des cases si le champ coord est mis à *true*, sinon affichage des cases normales
 *
 * @param ostream & - *flux*
 * @param bool - *coord*
 */
void Carte::afficherConsole(ostream &flux, bool coord)
{
    Vector2u vectCoord;
    for (uint i = 0; i < _nbLignesGrille; ++i)
    {
        if (i % 2 == 0)
        {
            flux << " "; // Décalage hexagonale
        }

        for (uint j = 0; j < _nbColonnesGrille; ++j)
        {
            if (coord)
            {
                vectCoord = getCoordCase(i, j);
                flux << "(" << vectCoord.x << "," << vectCoord.y << ") ";
            }
            else
            {
                _grille[i][j].afficherConsole(flux);
                flux << " ";
            }
        }
        flux << endl;
    }
}

void Carte::dessiner()
{
    for (uint y = 0; y < _nbLignesGrille; ++y)
    {
        for (uint x = 0; x < _nbColonnesGrille; ++x)
        {
            _grille[y][x].dessiner();
        }
    }
}

/*******************************************************/

void Carte::ajouterConstructionCaseCarte(Structure *s, const Vector2i &pos)
{
    _grille[pos.y][pos.x].ajouterConstruction(s);
}

/*******************************************************/