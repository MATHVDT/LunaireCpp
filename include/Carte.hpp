#ifndef __CARTE_HPP__
#define __CARTE_HPP__

#include <iostream>
#include <exception>
#include <math.h>

#include "Case.hpp"

using namespace std;

// class RenderWindow;

class Carte
{
private:
    int _dimensionGrille;
    Case **_grille; // Matrice [i][j] => i=y et j=x

    static int _test;
    static Carte *_singleton;

public:
    static Carte *getInstance();

public:
    ~Carte();

    void initCarte( RenderWindow &window,int taille = 20);

    // Affichage
    void afficherConsole(ostream &flux = cout, bool coord = false);
    void afficher(RenderWindow &window);

    // Getter
    int getDimensionGrille() const;

private:
    Carte();
    void ajustageCaseHexagone(RenderWindow &window);
    void deleteGrille();
};

// Methode inline
inline int Carte::getDimensionGrille() const
{
    return _dimensionGrille;
}

#endif