/**
 * @file Pipeline.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implémentation des méthodes de la classe Pipeline
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 */
#include "Pipeline.hpp"

// A deplacer dans un hpp qui regroupe tous les chemins
string cheminFichierTexturesPipelines = "ressource/cheminTexturesPipelines.txt";

uint Pipeline::_nbPipelines = 0;
uint Pipeline::_idMaxPipelines = 0;

const uint Pipeline::_tailleStockEntree = 1;
const uint Pipeline::_tailleStockSortie = 1;

uint Pipeline::_levelMax = 3;
//  uint Pipeline:: _nbAnim;   // = 1

uint Pipeline::_tailleTexture = 0; // 655

// 3 Textures : Pas connecté | droit | angle
Texture *Pipeline::_texturesPipelines[NB_TEXTURE];
uint Pipeline::_offsetTextureX = 655; // Largeur d'1 texture
uint Pipeline::_offsetTextureY = 655; // Hauteur d'1 texture

/**
 * @brief Construct a new Pipeline:: Pipeline object
 *
 * @param Vector2u & - *pos*
 */
Pipeline::Pipeline(const Vector2u &pos)
    : Structure{pos, _texturesPipelines[NON_CONNECTE],
                _tailleStockEntree, _tailleStockSortie},
      _idPipeline(++_idMaxPipelines),
      _zoomTexture{0, 0,
                   (int)_offsetTextureX,
                   (int)_offsetTextureY},
      _orientation{NULLDIRECTION, NULLDIRECTION,
                   NON_CONNECTE, A_A}
{
    ++_nbPipelines;
}

/**
 * @brief Destroy the Pipeline:: Pipeline object
 */
Pipeline::~Pipeline() { --_nbPipelines; }

/*******************************************************/
/*******************************************************/
/*******************************************************/

void Pipeline::chargerMemoirePipelines()
{
    // cerr << endl << "chargerMemoirePipelines" << endl;
    chargerTextures(cheminFichierTexturesPipelines);
    _offsetTextureX = _tailleTexture; // Largeur d'une case
    _offsetTextureY = _tailleTexture; // Largeur d'une case
}

void Pipeline::dechargerMemoirePipelines()
{
    cerr << endl
         << "dechargerMemoirePipelines" << endl;
    for (int i = 0; i < NB_TEXTURE; ++i)
    {
        delete _texturesPipelines[i];
    }
}

/*******************************************************/

/**
 * @brief Charge les textures des différentes Pipeline en mémoire dans une variable static *(à partir d'un fichier indiquant les chemins)*
 *
 * @param string - *fichierCheminsTexture*
 */
void Pipeline::chargerTextures(string fichierCheminsTexture)
{
    cerr << "nb texture enum :" << NB_TEXTURE << endl;
    string nomFichierTexture[NB_TEXTURE];
    string cheminTexture;
    sf::Texture *texture;

    ifstream monFlux;
    monFlux.open(fichierCheminsTexture);

    if (monFlux)
    {
        cerr << "Chargement des textures des Pipelines" << endl;
        // Récupération des chemins
        for (int k = 0; k < NB_TEXTURE; ++k)
        {
            // Chemin de l'image texture d'une Pipeline
            monFlux >> cheminTexture;
            cerr << cheminTexture << endl;

            // Create de la nouvelle texture
            texture = new Texture();
            texture->loadFromFile(cheminTexture);

            _texturesPipelines[k] = texture;
        }
        // Récupère la taille d'une case texture
        _tailleTexture = texture->getSize().y / 3;

        monFlux.close();
    }
    else
    {
        std::cerr << "/!\\ Erreur d'ouverture du fichier : " << fichierCheminsTexture << " /!\\" << endl;
    }
}

/*******************************************************/
/*******************************************************/

void Pipeline::init() {}

void Pipeline::dessiner(float scaleSprite)
{
    // cerr << "type : " << _orientation.type << endl;
    // cerr << "variant : " << _orientation.variant << endl;
    setSpriteTexture(0);
    Structure::dessiner(scaleSprite);
}

void Pipeline::update() {}

void Pipeline::process() {}

/*******************************************************/
/*******************************************************/

/**
 * @brief Zoom et rotate la texture du pipeline en fonction du niveau et de la position par rapport aux extremités
 *
 * @param uint - *tick*
 */
void Pipeline::setSpriteTexture(uint tick)
{
    _zoomTexture.top = _level * _offsetTextureY;

    // Changement de Type de Pipeline
    _sprite->setTexture(*_texturesPipelines[_orientation.type]);
    // Changement de Variant de Pipeline
    _zoomTexture.left = _orientation.variant * _offsetTextureX;

    _sprite->setTextureRect(_zoomTexture);

    // cerr << "type : " << _orientation.type << endl;
    // cerr << "variant : " << _orientation.variant << endl;
}

/*******************************************************/
/*******************************************************/

/**
 * @brief Check si la connexion entre le Pipeline et une autre strucutre est possible (nb de connexion)
 *
 * @details Dans la méthode override, on regarde si la structrures peut avoir une connexion suplémentaire (sortie ou entrée). Puis dans la méthode Structure::checkConnexionPossible, on regarde si c'est la structure que l'on veut ajouter qui peut accepter une connexion supplémentaire (entrée ou sortie).
 *
 * @param Structure * - *s*
 * @param bool - *commeSortie*
 *
 * @return true - *Connexion possible*
 * @return false - *Connexion impossible*
 */
bool Pipeline::checkConnexionPossible(Structure *s, bool commeSortie)
{
    return Structure::checkConnexionPossible(s, commeSortie);
}

/*******************************************************/

/**
 * @brief Calcule l'orientation de Pipeline en fct des connexions dessus
 *
 */
bool Pipeline::updateOrientation()
{
    Vector2i posEntree = Vector2i{-1, -1};
    Vector2i posSortie = Vector2i{-1, -1};

    if (this->getNbEntrees() >= 1)
    {
        posEntree = (Vector2i)(*getStructuresConnecteesEntrantes().begin())->getPositionCarte();
    }

    if (_sortie != nullptr)
        posSortie = (Vector2i)_sortie->getPositionCarte();

    DIRECTION dirEntree = positionOrigineDestToDirection((Vector2i)this->getPositionCarte(), posEntree);
    DIRECTION dirSortie = positionOrigineDestToDirection((Vector2i)this->getPositionCarte(), posSortie);

    _orientation.dirEntree = dirEntree;
    _orientation.dirSortie = dirSortie;

    return calculOrientation(dirEntree, dirSortie);
}

/**
 * @brief Inverse la connexion du Pipeline
 *
 * @todo Test si cest d'autre pipeline qui sont co pour inverser toute le pipeline complet
 *
 * @return true - *Si le Pipeline a changé de sens*
 * @return false - *Si le Pipeline n'a pas changé de sens*
 */
bool Pipeline::inverserSens()
{
    // Test que le pipeline est bien connecté dans les deux sens
    if (this->getNbConnexions() == 0)
        return false;

    Pipeline *curseurPipeline = this;
    Pipeline *precPipeline = this;
    Pipeline *premierMaillon = this;
    Pipeline *dernierMaillon = this;

    Structure *saveEntreePipeline = nullptr;
    Structure *saveSortiePipeline = nullptr;

    stack<Pipeline *> pilePipelineSortie{};

    /***** Parcours jusqu'au début du pipeline ********/
    while (curseurPipeline != nullptr &&
           curseurPipeline->getNbEntrees() == 1 &&
           typeid(*(curseurPipeline->getStructuresConnecteesEntrantes().front())) == typeid(Pipeline))
    {
        cerr << "parcours entree" << endl;
        precPipeline = curseurPipeline;
        curseurPipeline = (Pipeline *)curseurPipeline->getStructuresConnecteesEntrantes().front();
    }
    // Marquage du premier maillon
    premierMaillon = curseurPipeline;

    // Marquage du batiment en entrée
    if (premierMaillon != nullptr) // Normalement pas besoin
    {
        // A un batiment en entrée
        if (premierMaillon->getNbEntrees() == 1)
            saveEntreePipeline = premierMaillon->getStructuresConnecteesEntrantes().front();
        else // A pas de batiment en entrée
            saveEntreePipeline = nullptr;

        // Déconnecte le batiment en entrée si yen a un
        cerr << "deco premierMaillon : " << premierMaillon->deconnecterStructure(saveEntreePipeline) << endl;
    }

    /**************** SORTIE *******************/
    // Push du premier maillon dans la pile pour le traitement
    pilePipelineSortie.push(premierMaillon);

    // Parcours le chemin depuis sortie jusqu'a fin pipeline
    while (curseurPipeline != nullptr &&
           curseurPipeline->getASortie() == true &&
           typeid(*(curseurPipeline->getSortie())) == typeid(Pipeline))
    {
        // Récupération de la sortie
        precPipeline = curseurPipeline;
        curseurPipeline = (Pipeline *)curseurPipeline->getSortie();

        // Enregistrement du maillon du pipeline
        pilePipelineSortie.push(curseurPipeline);
        // Deconnexion de l'entrée
        precPipeline->deconnecterStructure(curseurPipeline);
    }
    // Marquage du dernier maillon
    dernierMaillon = pilePipelineSortie.top();

    // Marquage du batiment en sortie
    if (dernierMaillon != nullptr) // Normalement pas besoin
    {
        // A un batiment en sortie
        if (dernierMaillon->getASortie())
            saveSortiePipeline = dernierMaillon->getSortie();
        else // A pas de batiment en sortie
            saveSortiePipeline = nullptr;

        // Déconnecte le batiment en sortie si yen a un
        cerr << "deco dernierMaillon : " << dernierMaillon->deconnecterStructure(saveSortiePipeline) << endl;
    }

    /************* TEST INVERSION POSSIBLE *************/
    bool inverserSortie = true;
    bool inverserEntree = true;

    // Yavait un batiment en entrée
    cerr << "saveEntreePipeline : " << saveEntreePipeline << endl;
    if (saveEntreePipeline != nullptr)
    { // premierMaillon -> bat
        inverserEntree = saveEntreePipeline->connecterStructure(premierMaillon, false, false);
        cerr << "inverserEntree : " << inverserEntree << endl;
    }

    // Yavait un batiment en sortie
    cerr << "saveSortiePipeline : " << saveSortiePipeline << endl;
    if (saveSortiePipeline != nullptr)
    { // bat -> dernierMaillon
        inverserSortie = saveSortiePipeline->connecterStructure(dernierMaillon, true, false);
        cerr << "inverserSortie : " << inverserSortie << endl;
    }

    cerr << "inverserEntree : " << inverserEntree << endl;
    cerr << "inverserSortie : " << inverserSortie << endl;

    // Inverse tout si possible
    if (inverserEntree && inverserSortie)
    {
        // Connexion dans le sens inverse
        // bat -> dernierMaillon ... -> premierMaillon -> bat
        while ((int)pilePipelineSortie.size() > 1)
        {
            curseurPipeline = pilePipelineSortie.top();
            pilePipelineSortie.pop();

            cerr << curseurPipeline->connecterStructure(pilePipelineSortie.top(), true) << endl;
        }
    }
    else
    {

        // ReConnexion dans le d'avant sens
        // bat <- dernierMaillon ... <- premierMaillon <- bat
        while (pilePipelineSortie.size() > 1)
        {
            cerr << "On vide la pile" << endl;
            cerr << "Taille pile : " << (int)pilePipelineSortie.size() << endl;
            precPipeline = curseurPipeline;
            curseurPipeline = pilePipelineSortie.top();
            pilePipelineSortie.pop();

            printf("(%d, %d) -> ",
                   curseurPipeline->getPositionCarte().x,
                   curseurPipeline->getPositionCarte().y);
            printf("(%d, %d) \n\n",
                   pilePipelineSortie.top()->getPositionCarte().x,
                   pilePipelineSortie.top()->getPositionCarte().y);

            cerr << curseurPipeline->connecterStructure(pilePipelineSortie.top(), false) << endl;
        }
        if (!pilePipelineSortie.empty())
        {
            curseurPipeline = pilePipelineSortie.top();
            cerr << curseurPipeline << endl;
            cerr << "co : " << curseurPipeline->connecterStructure(premierMaillon, false) << endl;
            cerr << "co : " << premierMaillon->connecterStructure(curseurPipeline, false) << endl;
            cerr << "co : " << curseurPipeline->connecterStructure(premierMaillon, true) << endl;
            cerr << "co : " << premierMaillon->connecterStructure(curseurPipeline, true) << endl;
        }
        // premierMaillon <- bat
        cerr << "deco comme avant premierMaillon" << premierMaillon->deconnecterStructure(saveEntreePipeline) << endl;
        cerr << "reco comme avant premierMaillon" << premierMaillon->connecterStructure(saveEntreePipeline, false) << endl;

        // bat <- dernierMaillon
        cerr << "deco comme avant dernierMaillon" << dernierMaillon->connecterStructure(saveSortiePipeline, true) << endl;
        cerr << "reco comme avant dernierMaillon" << dernierMaillon->connecterStructure(saveSortiePipeline, true) << endl;
    }
    cerr << "FIN" << endl;

    // return false;
}
