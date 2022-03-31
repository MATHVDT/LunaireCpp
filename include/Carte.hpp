#ifndef __CARTE_HPP__
#define __CARTE_HPP__

#include <iostream>
#include <exception>

using namespace std;

class Carte
{
private:
    int _dimensionGrille;
    int **_grille; // Matrice [i][j] => i=y et j=x

    static Carte *_singleton;

public:
    static Carte *getInstance();

public:
    ~Carte();

    void initCarte(int taille = 20);

    // Affichage
    void afficherConsole(ostream &flux = cout, bool coord = false);

    // Getter
    int getDimensionGrille() const;

private:
    Carte();
    void deleteGrille();
};

// Methode inline
inline int Carte::getDimensionGrille() const
{
    return _dimensionGrille;
}

#endif