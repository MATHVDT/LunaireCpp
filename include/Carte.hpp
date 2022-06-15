/**
 * @file Carte.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Prototype des méthodes de la classe Carte
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 */
#ifndef __CARTE_HPP__
#define __CARTE_HPP__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <exception>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "CaseMap.hpp"
#include "ContextGlobal.hpp"

class CaseMap;
class Structure;
class ContextGlobal;

using namespace std;

extern ContextGlobal *contextGlobal;

class Carte
{
private:
    // Dimension Grille
    uint _nbLignesGrille;
    uint _nbColonnesGrille;
    // Dimension Carte
    uint _nbLignesCarte;   // 1 l_carte = 2 l_grille
    uint _nbColonnesCarte; // 2 c_carte = 1 c_grille
    CaseMap **_grille;     // Matrice [i][j] => i=y et j=x

    static int _test;
    static Carte *_singleton;

public:
    static Carte *getInstance();

public:
    ~Carte();

    void initCarte(const string nomFichierMap);
    void initCarte(uint nbLignes = 4,
                   uint nbCcolonnes = 4);

    // Affichage
    void afficherConsole(ostream &flux = cout, bool coord = false);
    void dessiner();

    // Getter
    Vector2u getDimensionGrille() const;
    uint getDimensionGrilleLigne() const;
    uint getDimensionGrilleColonne() const;
    Vector2u getDimensionCarte() const;
    uint getNbLignes() const;
    uint getNbColonnes() const;

    CaseMap **getCasesVoisines(const Vector2u &posCase, bool posCarte = true) const;

    CaseMap *getCaseToCoord(const Vector2f &point) const;

    // Setter
    void ajouterConstructionCaseCarte(Structure *s,
                                      const Vector2u &pos);

    // Convertisseur coordonnées
    static Vector2u matriceToCarte(const Vector2u &cMat);
    static Vector2u carteToMatrice(const Vector2u &cCarte);

    static Vector2f carteToPositionEcran(const Vector2u &cCarte);
    static Vector2u positionEcranToCarte(const Vector2f &cEcran);

    static Vector2u matriceToPositionEcran(const Vector2u &);
    static Vector2u positionEcranToMatrice(const Vector2u &);

private:
    Carte();
    void setCaseEcran();
    void deleteGrille();
    void creerGrille(uint nbLignes, uint nbColonnes);
};

#include "CarteInline.hpp"

#endif
