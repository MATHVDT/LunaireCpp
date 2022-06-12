#include "main.hpp"

// Surveiller que ca reste constant ...
// 705 blocs pas libérés dans la mémoire -> surement SFML
// 316 blocs pas libérés dans la mémoire dans TU

ContextGlobal *contextGlobal = ContextGlobal::getInstance();

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

    contextGlobal->init(Vector2u(1500, 800));

    CaseMap::chargerMemoireCaseMap();
    Mine::chargerMemoireMines();
    Pipeline::chargerMemoirePipelines();

    testCarte();

    CaseMap::dechargerMemoireCaseMap();
    Mine::dechargerMemoireMines();
    Pipeline::dechargerMemoirePipelines();

    delete contextGlobal;

    return 0;
}

void testCarte()
{

    Carte *carte = Carte::getInstance();
    carte->initCarte("./ressource/map.txt");
    std::cout << "carte : " << carte << std::endl;

    Mine *s = new Mine{Vector2u(0, 0)};
    s->init();
    carte->ajouterConstructionCaseCarte(s, s->getPosition());

    Mine *s2 = new Mine{Vector2u(5, 3)};
    s2->init();
    carte->ajouterConstructionCaseCarte(s2, s2->getPosition());

    Pipeline *p1 = new Pipeline(Vector2u(1, 1));
    Pipeline *p2 = new Pipeline(Vector2u(4, 0));
    carte->ajouterConstructionCaseCarte(p1, p1->getPosition());
    carte->ajouterConstructionCaseCarte(p2, p2->getPosition());

    while (contextGlobal->getIsRun())
    {
        while (contextGlobal->getPollEvent())
        {
        }
        contextGlobal->update();
        carte->dessiner();
        contextGlobal->afficherFenetre();
    }

    delete s;
    delete s2;
    delete p1;
    delete p2;
    delete carte;
}