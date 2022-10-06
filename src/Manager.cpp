#include "Manager.hpp"

Manager *Manager::_singleton;

uint Manager::_tailleTexture = 0;
Texture *Manager::_texturesManager[NB_TEXTURE_OVERLAY];

/**
 * @brief Constructeur du Manager *singleton*
 */
Manager::Manager() : _carte(Carte::getInstance()),
                     _endpointStructure{},
                     _spriteCaseOver(new Sprite),
                     _spriteCaseSelectionnee(new Sprite),
                     _menu{Menu::getInstance()}
{
}

Manager::~Manager()
{
    // delete _endpointStructure;

    delete _spriteCaseOver;
    delete _spriteCaseSelectionnee;
}
/******************************************************/

void Manager::init()
{
    cerr << "Init du MANAGER" << endl;
    uint nbBatiment = 2;
    size_t batimentHash[nbBatiment] =
        {typeid(Mine).hash_code(),
         typeid(Fonderie).hash_code()};

    auto it = listCraftsBatiment.begin();
    initCrafts();
    for (int i = 0; i < nbBatiment; ++i)
    {
        cerr << "hash : " << batimentHash[i] << endl;
        it++;
        (*it)->batiment = batimentHash[i];
    }

    // _carte = Carte::getInstance();
    _menu->init();

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

/*****************************************/
/*****************************************/

void Manager::chargerMemoireManager()
{
    cerr << endl
         << "chargerMemoireManager" << endl;
    chargerTextures("ressource/cheminTextures/cheminTexturesManager.txt");
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

/*****************************************/

/**
 * @brief Charge les textures du Manager en mémoire dans une variable static *(à partir d'un fichier indiquant les chemins)*
 *
 * @param string - *fichierCheminsTexture*
 */
void Manager::chargerTextures(string fichierCheminsTexture)
{
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

/*****************************************/
/*****************************************/

void Manager::dessiner()
{
    _menu->dessiner();

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

/**
 * @brief Process les Structures pour les actualiser, en partant du Marchand
 * @warning Si des structures ne sont pas connexe au Marchand, alors elle ne sont pas process
 *
 */
void Manager::updateStructure()
{

    queue<Structure *> queueStruct{_endpointStructure};
    // queue<Structure *> queueStruct{};

    Structure *curseurStruct = nullptr;
    connexion_t *c = nullptr;

    // cerr << "Nouveau tour d'update" << endl;

    while (!queueStruct.empty())
    {
        // Récuperation dans la file
        curseurStruct = queueStruct.front();
        queueStruct.pop();

        // Récupération de toutes les structures connectées entrantes
        // Pour remonter les connexions jusqu'aux extremités
        for (int dir = DIRECTION::NORD;
             dir <= DIRECTION::NORDEST;
             ++dir)
        {
            c = curseurStruct->getConnexions() + dir;

            if (c->type == TypeConnexion::Input)
            {
                if (c->structure == nullptr)
                {
                    cerr << "ERREUR connexion Input avec pas de structure" << endl;
                }
                queueStruct.push(c->structure);
            }
        }

        // Traitement de la structure
        cerr << "Update struct id : " << curseurStruct->getIdStructure() << endl;
        curseurStruct->update();
        // cerr << endl;
    }
    // cerr << endl;
}

void Manager::update()
{
    // Process les structures pour les actualiser
    updateStructure();
}

/**
 * @brief Boucle principale du jeu
 *
 */
void Manager::run()
{
    _carte->initCarte("./ressource/maps/map2.txt");

    float largeurCarteEcran = contextGlobal->getLargeurMapEcran();
    _menu->setPositionEcran(Vector2f{largeurCarteEcran, 0.f});

    while (contextGlobal->getIsRun())
    {
        while (contextGlobal->getPollEvent())
        { // Actualise le contexte seulement quand il ya une evenement
            contextGlobal->update();
            updateEvent();
        }

        if (contextGlobal->getUpdateTick())
        {
            // cout << endl;
            dessiner();
            contextGlobal->afficherFenetre();
            update();
            contextGlobal->setUpdateTick(false);
        }
    }
}

bool Manager::placerStructure()
{
    CaseMap *caseSelect = contextGlobal->getCaseSelectionnee();
    TYPE_STRUCTURE editionStructSelect = contextGlobal->getEditionStructureSelectionnee();

    // Test si on peut placer une structure
    if (editionStructSelect == TYPE_STRUCTURE::AucuneStructure ||
        caseSelect == nullptr ||
        caseSelect->getConstruction() != nullptr)
    {
        return false;
    }

    Structure *structAPlacer = nullptr;

    // switch (editionStructSelect)
    // {
    // case TYPE_STRUCTURE::Pipeline:
    //     structAPlacer = new Pipeline{(Vector2u)caseSelect->getPositionCarte()};
    //     break;
    // case TYPE_STRUCTURE::Mine:
    //     structAPlacer = new Mine{
    //         (Vector2u)caseSelect->getPositionCarte(),
    //         caseSelect->getTypeSol()};
    //     break;
    // case TYPE_STRUCTURE::Marchand:
    //     structAPlacer = new Marchand{
    //         (Vector2u)caseSelect->getPositionCarte()};
    //     _endpointStructure.push(structAPlacer);
    //     break;
    // default:
    //     break;
    // }

    switch (contextGlobal->getGameEvent())
    {
    case GameEvent::PlacerPipeline:
        structAPlacer = new Pipeline{(Vector2u)caseSelect->getPositionCarte()};
        break;
    case GameEvent::PlacerMarchand:
        structAPlacer = new Marchand{
            (Vector2u)caseSelect->getPositionCarte()};
        _endpointStructure.push(structAPlacer);
        break;

    case GameEvent::PlacerMine:
        structAPlacer = new Mine{
            (Vector2u)caseSelect->getPositionCarte(),
            caseSelect->getTypeSol()};
        break;
    case GameEvent::PlacerFonderie:
        structAPlacer = new Fonderie{
            (Vector2u)caseSelect->getPositionCarte()};
        _endpointStructure.push(structAPlacer);
        break;

    case GameEvent::PlacerFabrique:
        structAPlacer = new Fabrique{
            (Vector2u)caseSelect->getPositionCarte()};
        _endpointStructure.push(structAPlacer);
        break;
    case GameEvent::PlacerAtelier:
        structAPlacer = new Atelier{
            (Vector2u)caseSelect->getPositionCarte()};
        _endpointStructure.push(structAPlacer);
        break;

    case GameEvent::PlacerCuve:
        structAPlacer = new Cuve{
            (Vector2u)caseSelect->getPositionCarte()};
        _endpointStructure.push(structAPlacer);
        break;
    case GameEvent::PlacerChantierSpatial:
        structAPlacer = new ChantierSpatial{
            (Vector2u)caseSelect->getPositionCarte()};
        _endpointStructure.push(structAPlacer);
        break;
    default:
        break;
    }

    _carte->ajouterConstructionCaseCarte(structAPlacer, structAPlacer->getPositionCarte());

    // Structure placée -> intégration
    integrationStructureVoisinage();

    // Reset le choix de case select
    // A choisir si on deselectionne la case
    // après ajout d'une structure ???
    // A priori nn car on va avoir besoin de savoir
    // quelle case a été ajouté pour les calculs
    // de connexion et d'orientation
    contextGlobal->setCaseSelectionnee(true);

    contextGlobal->resetGameEvent();

    return true;
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
            // On essaye de connecter dans les 2 sens
            if (structAjoutee->connecterStructure(structsVoisines[k], false))
            {
                cerr << "Connexion Structure comme une entrée " << structAjoutee->getIdStructure() << " <- " << structsVoisines[k]->getIdStructure() << endl;
            }
            else if (structAjoutee->connecterStructure(structsVoisines[k], true))
            {
                cerr << "Connexion Structure comme une sortie " << structAjoutee->getIdStructure() << " -> " << structsVoisines[k]->getIdStructure() << endl;
            }
            else
            {
                cerr << "Pas connectée de : " << structAjoutee->getIdStructure() << " - " << structsVoisines[k]->getIdStructure() << endl;
            }
        }
    }

    // Optimisation des orientations et connexions
    // Du style changement de sens d'un pipeline complet
    // S'il n'est pas fixé/bloqué par des contraintes sépcifiques
    // ...

    // Adapatation des textures des structures impactées
    structAjoutee->updateOrientation();
    for (int k = 0; k < 6; ++k)
    {
        // Actualiser orientation structure (Texture)
        if (structsVoisines[k] != nullptr)
            structsVoisines[k]->updateOrientation();
    }

    return true;
}

/**
 * @brief Effectue les calculs et actions liées au context actualisé par les event
 *
 */
void Manager::updateEvent()
{
    placerStructure();

    CaseMap *caseSelect = contextGlobal->getCaseSelectionnee();
    Structure *structSelect = (caseSelect == nullptr ? nullptr : caseSelect->getConstruction());

    switch (contextGlobal->getGameEvent())
    {
    case GameEvent::InverserSensPipeline:
        inverserSensPipeline(structSelect);
        break;
    case GameEvent::ValiderCraft:
        cerr << "EVENT VALIDER CRAFT" << endl;
        validerCraft(structSelect);
        break;
    case GameEvent::ResetCraft:
        cerr << "EVENT RESET CRAFT" << endl;
        resetCraft(structSelect);
        break;

    default:
        break;
    }

    // Essayer de trouver une game event pour ca
    if (structSelect != nullptr)
    {
        if (isBatimentCraft(structSelect))
        {

            Batiment *bat = ((Batiment *)structSelect);
            if (!bat->getIsFormuleCraftDefine())
            {
                bat->checkCraftPossible();
                // Set menu bastselectUndefine
                _menu->setSectionMenu(SectionMenu::BatimentSelectCraftUndefine);
            }
            else
            {
                // _menu->setListFormuleCraft(bat->getFormuleCraft());
                _menu->setSectionMenu(SectionMenu::BatimentSelectCraftDefine);
                // Set Men bat select define
            }
        }
        _menu->setListCraftPossible(structSelect->getListCraftPossible());
    }
    else
    {
        // _menu->setListCraftPossible(nullptr);
        _menu->setSectionMenu(SectionMenu::ChoixStructures);
    }
}

/**
 * @brief Instructions à effectuer pour l'inversion d'un pipeline.
 *
 * @param Structure * - *structSelect*
 */
void Manager::inverserSensPipeline(Structure *structSelect)
{

    if (structSelect != nullptr &&
        typeid(*structSelect).hash_code() == typeid(Pipeline).hash_code())
    {
        ((Pipeline *)structSelect)->inverserSens();
        // ((Pipeline *)structSelect)->updateOrientation();
        contextGlobal->resetGameEvent();
    }
}

/**
 * @brief Test si la structure est bien un Batiment et à des crafts.
 *
 * @details Test si c'est un des Batiments suivant :
 * - Mine
 * - Fonderie
 *
 * @param Structure * - *s*
 * @return true - *Bien un Batiment avec des crafts*
 * @return false - *Pas un Batiment avec des crafts*
 */
bool Manager::isBatimentCraft(Structure *s)
{
    return (typeid(*s).hash_code() ==
                typeid(Mine).hash_code() ||
            typeid(*s).hash_code() ==
                typeid(Fonderie).hash_code());
}

/**
 * @brief Valide le craft d'un batiment s'il est bien selectionné.
 *
 * @param Structure * - *s*
 */
void Manager::validerCraft(Structure *s)
{
    // Vérife que c'est bien en batiment mais normalement oui
    if (isBatimentCraft(s))
    { // Récup de la ressource select à craft
        TYPE_RESSOURCE rCraft = _menu->getRessourceCraftSelect();

        cout << "Ress select : " << ressString[rCraft] << endl;

        if (rCraft != TYPE_RESSOURCE::Rien)
        {
            cout << "Manager valider Craft ok" << endl;
            // Set la formule
            ((Batiment *)s)->setFormuleCraft(rCraft);

            _menu->setSectionMenu(SectionMenu::BatimentSelectCraftDefine);
        }
    }
    contextGlobal->resetGameEvent();
}

/**
 * @brief Reset le craft d'un batiment s'il est bien selectionné.
 *
 * @param Structure * - *s*
 */
void Manager::resetCraft(Structure *s)
{
    if (isBatimentCraft(s))
    {
        ((Batiment *)s)->resetFormuleCraft();
    }
    else
    {
        cerr << "Pas Un batiment avec des crafts, peut être un pb car pas censé arriver" << endl;
    }
    contextGlobal->resetGameEvent();
}
