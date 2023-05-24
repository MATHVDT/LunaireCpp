#include "main.hpp"

// Surveiller que ca reste constant ...
// 705 blocs pas libérés dans la mémoire -> surement SFML
// 316 blocs pas libérés dans la mémoire dans TU

ContextGlobal *contextGlobal = ContextGlobal::getInstance();

void testCarte();
void testCraft();
void testPartie();

int main()
{
    // testCraft();

    testPartie();

    delete contextGlobal;

    return 0;
}

void testCraft()
{
    // hash des batiments sont chargés dans le manager.init()

    initCrafts();
    uint nbBatiment = 2;
    // ATTENTION Hash inverser ....
    size_t batimentHash[nbBatiment] =
        {typeid(Fonderie).hash_code(),
         typeid(Mine).hash_code()};

    auto it = listCraftsBatiment.begin();
    initCrafts();
    for (int i = 0; i < nbBatiment; ++i)
    {
        cerr << "hash : " << batimentHash[i] << endl;
        it++;
        (*it)->batiment = batimentHash[i];
    }

    // Affichage formules craft
    // afficherFormuleCraft();

    TYPE_RESSOURCE stock[NB_CONNEXIONS];

    stock[0] = TYPE_RESSOURCE::Rien;
    stock[1] = TYPE_RESSOURCE::Rien;
    stock[2] = TYPE_RESSOURCE::Rien;
    stock[3] = TYPE_RESSOURCE::Rien;
    stock[4] = TYPE_RESSOURCE::Rien;
    stock[5] = TYPE_RESSOURCE::Rien;

    const size_t hash = typeid(Mine).hash_code();

    auto list = craftPossible(hash, stock);
    cout << "Affichage ressources crafatables : " << list.size() << endl;
    for (auto x : list)
    {
        cout << (short)x << " " << endl;
    }

    deleteCraft();
}

void testPartie()
{
    contextGlobal->init(Vector2u(1600, 900));

    CaseMap::chargerMemoireCaseMap();

    Pipeline::chargerMemoirePipelines();
    Marchand::chargerMemoireMarchand();

    Mine::chargerMemoireMines();
    Fonderie::chargerMemoireFonderies();

    Fabrique::chargerMemoireFabriques();
    Atelier::chargerMemoireAteliers();

    Cuve::chargerMemoireCuves();
    ChantierSpatial::chargerMemoireChantierSpatials();

    Manager::chargerMemoireManager();
    Bouton::chargerMemoireBoutons();
    IconeManager::chargerMemoireIcones();

    Manager *m = Manager::getInstance();
    m->init();

    m->run();

    CaseMap::dechargerMemoireCaseMap();

    Pipeline::dechargerMemoirePipelines();
    Marchand::dechargerMemoireMarchand();

    Mine::dechargerMemoireMines();
    Fonderie::dechargerMemoireFonderies();

    Fabrique::dechargerMemoireFabriques();
    Atelier::dechargerMemoireAteliers();

    Cuve::dechargerMemoireCuves();
    ChantierSpatial::dechargerMemoireChantierSpatials();

    Manager::dechargerMemoireManager();
    Bouton::dechargerMemoireBoutons();
    IconeManager::dechargerMemoireIcones();

    delete m;
}

/*
void testCarte()
{

    Carte *carte = Carte::getInstance();
    carte->initCarte("./ressource/map.txt");
    std::cout << "carte : " << carte << std::endl;

    Mine *s = new Mine{Vector2u(0, 0)};
    s->init();
    carte->ajouterConstructionCaseCarte(s, s->getPositionCarte());

    Mine *s2 = new Mine{Vector2u(5, 3)};
    s2->init();
    carte->ajouterConstructionCaseCarte(s2, s2->getPositionCarte());

    Pipeline *p1 = new Pipeline(Vector2u(1, 1));
    Pipeline *p2 = new Pipeline(Vector2u(4, 0));
    carte->ajouterConstructionCaseCarte(p1, p1->getPositionCarte());
    carte->ajouterConstructionCaseCarte(p2, p2->getPositionCarte());

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
*/