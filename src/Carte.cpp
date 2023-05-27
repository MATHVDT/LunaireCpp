/**
 * @file Carte.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implémentation des méthodes de la classe Carte
 *
 * @version 0.1
 * @date 2022-03-30
 *
 * @copyright Copyright (c) 2022
 */
#include "Carte.hpp"

Carte *Carte::_singleton = nullptr;

/**
 * @brief Récupère ou crée un instance de la carte *(patron de singleton)*
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
                _grille[i][j].setTypeSol(static_cast<TYPE_SOL>(typeSol));
                _grille[i][j].setSpriteTexture(static_cast<TYPE_SOL>(typeSol));
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
            _grille[i][j].setPositionCarte(coordCarte);
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
                vectCoord = matriceToCarte(Vector2u(j, i));
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
            // TEMPORAIRE de recalculer toutes les orientations à chaque dessin
            if (_grille[y][x].getConstruction() != nullptr)
            {
                _grille[y][x].getConstruction()->updateOrientation();
            }
            _grille[y][x].dessiner();
        }
    }
}

/*******************************************************/
/**
 * @brief Ajoute une structure sur la carte à la position indiquée.
 *
 * @param Structure * - *s*,
 * @param const Vector2u & - *posCarte*
 */
void Carte::ajouterConstructionCaseCarte(Structure *s, const Vector2u &posCarte)
{
    Vector2u posMatrice = carteToMatrice(posCarte);
    _grille[posMatrice.y][posMatrice.x].ajouterConstruction(s);

    // Si c'est pipeline gerer connexion
}

bool Carte::supprimerConstructionCaseCarte(Structure *s)
{
    for (uint y = 0; y < _nbLignesGrille; ++y)
    {
        for (uint x = 0; x < _nbColonnesGrille; ++x)
        {
            if (_grille[y][x].getConstruction() == s)
            {
                _grille[y][x].retirerConstruction();
                return true;
            }
        }
    }
    return false;
}

/*******************************************************/

/**
 * @brief Convertir une position dans la carte hexagonale en position sur l'écran
 *
 * @param const Vector2u& - *cCarte*
 * @return Vector2f
 */
Vector2f Carte::carteToPositionEcran(const Vector2u &cCarte)
{
    float tailleCaseMap = CaseMap::getTailleCaseMap();
    float xEcran = 0.f;
    float yEcran = 0.f;
    // Décalage 1 ligne sur deux
    xEcran += (float)(cCarte.x % 2) * 0.75f * tailleCaseMap;
    // Décalage pour former la ligne
    // xEcran += ((float)cCarte.x - (float)(cCarte.x % 2)) * tailleCaseMap * 0.75f; // Equivalent à la ligne du dessous
    xEcran += (float)((int)(cCarte.x / 2)) * tailleCaseMap * 1.5f;

    // Décalage pour faire la demi interligne ...
    yEcran += (float)(1 - cCarte.x % 2) * tailleCaseMap / 2.f;
    // Décalage pour faire les lignes
    yEcran += (float)cCarte.y * tailleCaseMap;

    // printf("(%5d,%5d) et (%5f,%5f)\n\n", cCarte.x, cCarte.y, xEcran, yEcran);

    return Vector2f(xEcran, yEcran);
}

/**
 * @brief Renvoie un tableau contenant les 6 cases voisines de la position indiquée.
 *
 * @param Vector2u & - *posCase* *(par défault position de la case en coordonnés Carte)*
 * @param bool - *posCarte = true* *(préciser le type de coordonnées de la case)**
 *
 * @return CaseMap**
 */
CaseMap **Carte::getCasesVoisines(const Vector2u &posCase, bool posCarte) const
{
    // Coord carte pour manilpuler les directions
    Vector2u coordCaseCarte;
    if (posCarte) // Coord en carte
    {             // On garde les coord fournit
        coordCaseCarte = posCase;
    }
    else // Coord en matrice
    {    // On convertit en coord carte
        coordCaseCarte = matriceToCarte(posCase);
    }

    CaseMap **voisinage = new CaseMap *[6]();
    Vector2i coordDir;
    Vector2i coordCaseVoisinePos;
    Vector2u coordCaseVoisineMatricePos;

    // Récupération des cases voisines
    for (int dir = DIRECTION::NORD;
         dir <= DIRECTION::NORDEST; ++dir)
    { // Pour chaque direction

        // Récupération de la position de la case voisine
        coordCaseVoisinePos = positionCaseVoisine(coordCaseCarte, dir);

        // Test si la case est dans la carte
        if (coordCaseVoisinePos.x >= 0 &&
            coordCaseVoisinePos.x < _nbColonnesCarte &&
            coordCaseVoisinePos.y >= 0 &&
            coordCaseVoisinePos.y < _nbLignesCarte)
        { // On est bien dans la carte

            // Transformation en coord Matrice
            coordCaseVoisineMatricePos = (Vector2u)carteToMatrice((Vector2u)coordCaseVoisinePos);

            // Ajout au voisinage
            voisinage[(int)dir] = &_grille[coordCaseVoisineMatricePos.y][coordCaseVoisineMatricePos.x];
        }
        else // En dehors de la carte
        {    // Pas de case voisine dans cette directions
            voisinage[(int)dir] = nullptr;
        }
    }
    // Affichage du voisinage
    // for (int i = 0; i < 6; ++i)
    // {
    //     cerr << "dir " << i;
    //     if (voisinage[i] != nullptr)
    //         cerr << " case" << endl;
    //     else
    //         cerr << " nullptr" << endl;
    // }
    return voisinage;
}

float distanceEuclidienne(const Vector2f &p1, const Vector2f &p2)
{
    // cout << "srt : " << sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)) << endl;

    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                (p1.y - p2.y) * (p1.y - p2.y));
}

CaseMap *Carte::getCaseToCoord(const Vector2f &point) const
{
    if (_grille != nullptr)
    {
        float tailleCase = contextGlobal->getTailleReference();
        float distance;
        float distanceMin = 9999.f;

        Vector2f posCaseCentre{0.f, 0.f};

        Vector2u posCaseMatriceSave{0, 0};

        for (uint y = 0; y < _nbLignesGrille; ++y)
        {
            for (uint x = 0; x < _nbColonnesGrille; ++x)
            {
                posCaseCentre = _grille[y][x].getPositionSprite();
                posCaseCentre.x += 0.5 * tailleCase;
                posCaseCentre.y += 0.5 * tailleCase;

                distance = distanceEuclidienne(posCaseCentre, point);
                if (distance < distanceMin)
                {
                    distanceMin = distance;
                    posCaseMatriceSave.x = x;
                    posCaseMatriceSave.y = y;
                }
            }
        }

        // Print coordCarte case
        // Vector2u posCaseCarteSave = matriceToCarte(posCaseMatriceSave);
        // cout << "case select : " << posCaseCarteSave.x << ", " << posCaseCarteSave.y << endl;
        // cout << "Pos souris : " << point.x << ", " << point.y << endl;

        return &_grille[posCaseMatriceSave.y][posCaseMatriceSave.x];
    }
    else
    {
        return nullptr;
    }
}
