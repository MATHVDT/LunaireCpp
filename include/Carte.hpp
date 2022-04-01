#ifndef __CARTE_HPP__
#define __CARTE_HPP__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <exception>
#include <math.h>

#include "Case.hpp"

using namespace std;

class Carte
{
private:
    // Dimension Grille
    uint _nbLignesGrille;
    uint _nbColonnesGrille;
    // Dimension Carte
    uint _nbLignesCarte;   // 1 l_carte = 2 l_grille
    uint _nbColonnesCarte; // 2 c_carte = 1 c_grille
    Case **_grille;        // Matrice [i][j] => i=y et j=x

    static int _test;
    static Carte *_singleton;

public:
    static Carte *getInstance();

public:
    ~Carte();

    void initCarte(RenderWindow &window,
                   const string nomFichierMap);
    void initCarte(RenderWindow &window,
                   uint nbLignes = 4,
                   uint nbCcolonnes = 4);

    // Affichage
    void afficherConsole(ostream &flux = cout, bool coord = false);
    void afficher(RenderWindow &window);

    // Getter
    Vector2u getDimensionGrille() const;
    uint getDimensionGrilleLigne() const;
    uint getDimensionGrilleColonne() const;
    Vector2u getDimensionCarte() const;
    uint getNbLignes() const;
    uint getNbColonnes() const;

    Vector2u getCoordCase(uint i, uint j) const;

private:
    Carte();
    void ajustageCasesHexagone(RenderWindow &window);
    void deleteGrille();
    void creerGrille(uint nbLignes, uint nbColonnes);
};

// Methode inline
inline Vector2u Carte::getDimensionGrille() const { return Vector2u{_nbColonnesGrille, _nbLignesGrille}; }

inline uint Carte::getDimensionGrilleLigne() const { return _nbLignesGrille; }

inline uint Carte::getDimensionGrilleColonne() const { return _nbColonnesGrille; }

inline Vector2u Carte::getDimensionCarte() const { return Vector2u(_nbColonnesCarte, _nbLignesCarte); }
inline uint Carte::getNbLignes() const { return _nbLignesCarte; }
inline uint Carte::getNbColonnes() const { return _nbLignesCarte; }

inline Vector2u Carte::getCoordCase(uint i, uint j) const
{
    return Vector2u(2 * j + (1 - (i % 2)), i / 2);
}

#endif
