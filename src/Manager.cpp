#include "Manager.hpp"

Manager *Manager::_singleton;

uint Manager::_tailleTexture = 0;
Texture *Manager::_texturesManager[NB_TEXTURE_OVERLAY];

/**
 * @brief Constructeur du Manager *singleton*
 */
Manager::Manager() : _carte(Carte::getInstance()),
                     _spriteCaseOver(new Sprite),
                     _spriteCaseSelectionnee(new Sprite) {}
/******************************************************/

void Manager::init()
{
    // _carte = Carte::getInstance();
    _spriteCaseOver->setTexture(*_texturesManager[CASE_OVER]);
    _spriteCaseSelectionnee->setTexture(*_texturesManager[CASE_SELECTIONNEE]);
}

/**
 * @brief Récupère ou crée un instance de manager *(patron de singleton)*
 * @warning Penser à delete le singleton
 * @return Manager * - *_singleton*
 */
Manager *Manager::getInstance()
{
    // Pas d'instance créée => alors création
    if (Manager::_singleton == nullptr)
        _singleton = new Manager{};
    return _singleton;
}

void Manager::chargerMemoireManager()
{
    cerr << endl
         << "chargerMemoireManager" << endl;
    chargerTextures("ressource/cheminTexturesManager.txt");
}

void Manager::dechargerMemoireManager()
{
    cerr << endl
         << "dechargerMemoireManager" << endl;
    for (int i = 0; i < NB_TEXTURE_OVERLAY; ++i)
    {
        delete _texturesManager[i];
    }
}

/**
 * @brief Charge les textures du Manager en mémoire dans une variable static *(à partir d'un fichier indiquant les chemins)*
 *
 * @param string - *fichierCheminsTexture*
 */
void Manager::chargerTextures(string fichierCheminsTexture)
{
    string nomFichierTexture[NB_RESSOURCES];
    string cheminTexture;
    sf::Texture *texture;

    ifstream monFlux;
    monFlux.open(fichierCheminsTexture);

    if (monFlux)
    {
        cerr << "Chargement des textures du Manager" << endl;
        // Récupération des chemins
        for (int k = 0; k < NB_TEXTURE_OVERLAY; ++k)
        {
            // Chemin de l'image texture d'une mine
            monFlux >> cheminTexture;
            cerr << cheminTexture << endl;

            // Create de la nouvelle texture
            texture = new Texture();
            texture->loadFromFile(cheminTexture);

            _texturesManager[k] = texture;
        }
        _tailleTexture = texture->getSize().x;

        monFlux.close();
    }
    else
    {
        std::cerr << "/!\\ Erreur d'ouverture du fichier : " << fichierCheminsTexture << " /!\\" << endl;
    }
}

/******************************************************/
void Manager::dessiner()
{
    // _menu->dessiner();
    _carte->dessiner();
    dessinerOverlay();
}

void Manager::dessinerOverlay()
{
    dessinerOverlayMap();
}

/**
 * @brief Dessine l'overlay du jeu dans le renderer
 *
 */
void Manager::dessinerOverlayMap()
{
    // Redimensionnement
    float scale = contextGlobal->getScaleReference();
    _spriteCaseOver->setScale(scale, scale);
    _spriteCaseSelectionnee->setScale(scale, scale);

    // Overlay de la carte
    if (contextGlobal->getCaseOver() != nullptr)
        contextGlobal->dessinerFenetre(_spriteCaseOver);

    if (contextGlobal->getCaseSelectionnee() != nullptr)
        contextGlobal->dessinerFenetre(_spriteCaseSelectionnee);
}

/******************************************************/

/**
 * @brief Calcule la case sourvolée par la souris
 *
 */
void Manager::calculCaseOver()
{
    CaseMap *caseMapOver = nullptr;
    const RenderWindow &win = contextGlobal->getWindow();

    uint largeurMap = contextGlobal->getTailleReference() / 4 * (3 * _carte->getNbColonnes() + 1);

    Vector2i mousePos = Mouse::getPosition(win);
    Vector2f mousePosFloat{(float)mousePos.x, (float)mousePos.y};

    if (mousePos.x > 0 &&
        mousePos.x < largeurMap &&
        mousePos.x < win.getSize().x &&
        mousePos.y > 0 &&
        mousePos.y < win.getSize().y)
    {
        caseMapOver = _carte->getCaseToCoord(mousePosFloat);
        _spriteCaseOver->setPosition(caseMapOver->getPosition());
    }
    // Enregistrement de la case dans le context
    contextGlobal->setCaseOver(caseMapOver);
}

/******************************************************/

void Manager::update()
{
    calculCaseOver();
}

/**
 * @brief Boucle principale du jeu
 *
 */
void Manager::run()
{
    _carte->initCarte("./ressource/map.txt");

    // Mine *s = new Mine{Vector2u(0, 0)};
    // s->init();
    // carte->ajouterConstructionCaseCarte(s, s->getPosition());

    // Mine *s2 = new Mine{Vector2u(5, 3)};
    // s2->init();
    // carte->ajouterConstructionCaseCarte(s2, s2->getPosition());

    // Pipeline *p1 = new Pipeline(Vector2u(1, 1));
    // carte->ajouterConstructionCaseCarte(p1, p1->getPosition());

    while (contextGlobal->getIsRun())
    {
        while (contextGlobal->getPollEvent())
        {
        }
        contextGlobal->update();
        update();
        dessiner();
        contextGlobal->afficherFenetre();
    }

    // delete s;
    // delete s2;
    // delete p1;
}