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

    testCraft();

    // testPartie();

    delete contextGlobal;

    return 0;
}

void testCraft()
{
    initCrafts();
    initFormulesCraft();

    // Affichage formules craft
    // afficherFormuleCraft();

    queue<TYPE_RESSOURCE> stock;
    stock.push(TYPE_RESSOURCE::LingotFer);
    stock.push(TYPE_RESSOURCE::MineraiFer);
    stock.push(TYPE_RESSOURCE::Rien);
    stock.push(TYPE_RESSOURCE::LingotFer);
    stock.push(TYPE_RESSOURCE::Rien);
    stock.push(TYPE_RESSOURCE::MineraiFer);
    stock.push(TYPE_RESSOURCE::MineraiFer);

    const size_t hash = typeid(Mine).hash_code();

    CraftPossible(hash, stock);
}

void testPartie()
{
    contextGlobal->init(Vector2u(1600, 900));

    CaseMap::chargerMemoireCaseMap();
    Mine::chargerMemoireMines();
    Pipeline::chargerMemoirePipelines();
    Manager::chargerMemoireManager();
    ContenuPipeline::chargerMemoireTypeRessource();
    MasterBatiment::chargerMemoireMasterBatiment();
    Bouton::chargerMemoireBoutons();

    Manager *m = Manager::getInstance();
    m->init();

    m->run();

    CaseMap::dechargerMemoireCaseMap();
    Mine::dechargerMemoireMines();
    Pipeline::dechargerMemoirePipelines();
    Manager::dechargerMemoireManager();
    ContenuPipeline::dechargerMemoireTypeRessource();
    MasterBatiment::dechargerMemoireMasterBatiment();
    Bouton::dechargerMemoireBoutons();

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