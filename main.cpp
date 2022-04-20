#include "main.hpp"

ContextGlobal &contextGlobal = ContextGlobal::getInstance();

void testCarte();

int main()
{
    // testSFML();

    // testSFML2();

    // Vector2u v(4, 3);
    // cout << "v_x  : " << v.x << ", v_y  : " << v.y << endl;

    // // Vector2u vt = Carte::matriceToCarte(v);
    // Vector2u vt = Carte::carteToMatrice(v);
    // cout << "vt_x : " << vt.x << ", vt_y : " << vt.y << endl;

    contextGlobal.init(Vector2u(1500, 800));

    CaseMap::chargerMemoireCaseMap();
    Mine::chargerMemoireMines();

    testCarte();

    CaseMap::dechargerMemoireCaseMap();
    Mine::dechargerMemoireMines();

    return 0;
}

void testCarte()
{

    int nbLignes = 1;
    int nbColonnes = 1;
    CaseMap::setScaleCaseMap(nbLignes,
                             nbColonnes);

    Carte *carte = Carte::getInstance();
    carte->initCarte("./ressource/map.txt");

    Structure *s = new Mine{Vector2u(0, 0)};

    carte->ajouterConstructionCaseCarte(s, Vector2u(0, 0));
    // carte->dessiner();
    // contextGlobal.afficherFenetre();

    while (contextGlobal.getIsRun())
    {
        while (contextGlobal.getPollEvent())
        {
        }
        contextGlobal.update();
        carte->dessiner();
        contextGlobal.afficherFenetre();
    }

    // carte->dessiner();
    // contextGlobal.afficherFenetre();

    delete s;
    delete carte;
}