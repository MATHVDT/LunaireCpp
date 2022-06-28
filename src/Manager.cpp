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

Manager::~Manager()
{
    delete _carte;
}
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

    // Overlay de la carte
    if (contextGlobal->getCaseOver() != nullptr)
    { // Set Texture : scale + position
        _spriteCaseOver->setScale(scale, scale);
        _spriteCaseOver->setPosition(contextGlobal->getCaseOver()->getPositionSprite());
        contextGlobal->dessinerFenetre(_spriteCaseOver);
    }
    if (contextGlobal->getCaseSelectionnee() != nullptr)
    { // Set Texture : scale + position
        _spriteCaseSelectionnee->setScale(scale, scale);
        _spriteCaseSelectionnee->setPosition(contextGlobal->getCaseSelectionnee()->getPositionSprite());
        contextGlobal->dessinerFenetre(_spriteCaseSelectionnee);
    }
}

void Manager::update()
{
}

/**
 * @brief Boucle principale du jeu
 *
 */
void Manager::run()
{
    _carte->initCarte("./ressource/map.txt");

    while (contextGlobal->getIsRun())
    {
        while (contextGlobal->getPollEvent())
        { // Actualise le contexte seulement quand il ya une evenement
            contextGlobal->update();
            placerStructure();
        }
        update();
        dessiner();
        contextGlobal->afficherFenetre();
    }
}

/**
 * @brief Place une Structure sur une case si toutes les conditions sont réunis
 * @details Conditions : une case est selectionnée, il n'y a pas de construction sur la case selectionnée, un type de structure est selectionné
 * Appelle les fonctions placerPipeline et placerMine
 *
 * @return true - *Si une structure à été placée*
 * @return false - *Aucune structure placée*
 */
bool Manager::placerStructure()
{
    bool structPlacee = false;
    CaseMap *caseSelect = contextGlobal->getCaseSelectionnee();

    TYPE_STRUCTURE editionStructSelect = contextGlobal->getEditionStructureSelectionnee();

    if (editionStructSelect != TYPE_STRUCTURE::AucuneStructure)
    { // Il y a un type de structure select
        if (caseSelect != nullptr)
        { // Case selectionnee
            if (caseSelect->getConstruction() == nullptr)
            { // Pas de structure sur la case choisie
                structPlacee = placerPipeline(caseSelect, editionStructSelect);
                if (!structPlacee)
                {
                    structPlacee = placerMine(caseSelect, editionStructSelect);
                    if (!structPlacee)
                    {
                        // cerr << "Pas de structure posée" << endl;
                    }
                }
            }
        }
    }

    // Structure placée -> intégration
    if (structPlacee)
        integrationStructureVoisinage();

    // Reset le choix de case select
    // A choisir si on deselectionne la case
    // après ajout d'une structure ???
    // A priori nn car on va avoir besoin de savoir
    // quelle case a été ajouté pour les calculs
    // de connexion et d'orientation
    // contextGlobal->setCaseSelectionnee(true);

    // Reset le choix d'edition de structure select
    contextGlobal->setEditionStructureSelectionnee(TYPE_STRUCTURE::AucuneStructure);

    return structPlacee;
}

/**
 * @brief Place une Mine sur la carte
 *
 * @todo  Spécifier juste pour les Mines : typeStructureToTypeRessource
 *
 * @param CaseMap * - *caseSelect*
 * @return true - Structure placée (Mine)
 * @return false - Structure non placée (Pas Mine)
 */
bool Manager::placerMine(CaseMap *caseSelect, TYPE_STRUCTURE editionStruct)
{
    bool place = false;

    TYPE_RESSOURCE ress = TYPE_RESSOURCE::Rien;

    // Spécifier juste pour les Mines
    ress = typeMineToTypeRessource(editionStruct);

    // Construit et ajoute la Mine
    if (ress != TYPE_RESSOURCE::Rien)
    {
        Mine *m = new Mine{
            (Vector2u)caseSelect->getPositionCarte(),
            caseSelect->getTypeSol(),
            ress};

        _carte->ajouterConstructionCaseCarte(m, m->getPositionCarte());

        place = true;
    }

    return place;
}

/**
 * @brief Place un Pipeline sur la carte
 *
 * @warning Ne connecte pas le Pipeline aux structures voisines
 *
 * @param CaseMap * - *caseSelect*
 * @return true - Structure placée (Pipeline)
 * @return false - Structure non placée (Pas Pipeline)
 */
bool Manager::placerPipeline(CaseMap *caseSelect, TYPE_STRUCTURE editionStruct)
{
    bool place = false;

    if (editionStruct == TYPE_STRUCTURE::Pipeline)
    {
        Pipeline *p = new Pipeline{(Vector2u)caseSelect->getPositionCarte()};

        _carte->ajouterConstructionCaseCarte(p, p->getPositionCarte());

        place = true;
    }

    return place;
}

/**
 * @brief Intègre une structure dans la carte par rapport à son voisinage. (gère le connexion et rotation des textures)
 *
 * @return true - *Intégration ok*
 * @return false - *Intégration pas ok*
 */
bool Manager::integrationStructureVoisinage()
{
    CaseMap *caseSelect = contextGlobal->getCaseSelectionnee();

    // Erreur normalement on devrait pas avoir nullptr
    // car la case n'a pas été deselectionnée
    if (caseSelect == nullptr)
        return false;

    Structure *structAjoutee = caseSelect->getConstruction();

    // Erreur normalement on devrait pas avoir nullptr
    // Enfin quand toutes les structures auront été imlémentées ;)
    if (structAjoutee == nullptr)
        return false;

    // Récupération voisinages de cases
    CaseMap **casesVoisines = _carte->getCasesVoisines(structAjoutee->getPositionCarte());

    // Récupération voisinage de structures
    Structure **structsVoisines = new Structure *[6];

    for (uint k = 0; k < 6; ++k)
    { // Si ya une case et une structure on la récupère
        // Bord de la map, il n'y a pas forcement de cases voisines
        if (casesVoisines[k] != nullptr)
            structsVoisines[k] = casesVoisines[k]->getConstruction();
        else // Pas de case (normalement pas besoin)
            structsVoisines[k] = nullptr;
    }

    // .... ajouterStruct ....
    // Garder une mémoire de la précedente case select pour une amélioration de la connection plus intuitive
    /* Pour l'instant
    On parcourt les cases voisines dans
    ordre habituel N->NO->...->NE
    la première structure trouvée est une sortie
    si sortie pas possible alors on connecte comme entrée
    dès que une sortie a été setter, tous les autres connexions
    sont des entrées
    */
   // Connexion des Structures à celle ajoutée
    for (int k = 0; k < 6; ++k)
    { // Pour chaque structure voisine
        if (structsVoisines[k] != nullptr)
        {
            if (!structAjoutee->getASortie())
            { // Essaye d'ajouter en sortie la structure
                if (structAjoutee->connecterStructure(structsVoisines[k], true))
                    cerr << "Connexion Structure comme une sortie" << endl;
            }
            // Dans tous les cas essaye d'ajouter comme entrée
            if (structAjoutee->connecterStructure(structsVoisines[k], false))
                cerr << "Connexion Structure comme une entrée" << endl;
        }
    }

    // Optimisation des orientations et connexions
    // Du style changement de sens d'un pipeline complet
    // S'il n'est pas fixé/bloqué par des contraintes sépcifiques
    // ...

    // Adapatation des textures des structures impactées
    // structAjoutee.updateOrientation();
    for (int k = 0; k < 6; ++k)
    {
        // Actualiser orientation structure (Texture)
        // structsVoisines[k].updateOrientation();
    }

    return true;
}
