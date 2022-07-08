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
 * @details Récuperer les extrémités du pipeline en parcours (tout en déconnectant les maillons du pipeline entre eux) :
 * - depuis les entrées tant qu'il s'agit d'un pipeline (pour obtenir le batiment en entrée)
 * - depuis les sortie tant qu'il s'agit d'un pipeline (pour obtenir le batiment en sortie)
 * Une fois les extremités récupérées, si y a des Batiments, alors on essaye de connecter dans l'autre sens les maillons de pipeline qui s'y connecte.
 * Si c'est Ok pour les deux cotés, alors on reconnecte dans l'autre sens tous les maillons entre eux, en partant de la sortie jusqu'à l'entrée*. (Utilisation d'une pile remplie de l'entrée jusqu'à la sortie dans un premier temps lorsque l'on cherche les extremités, puis dépilée de la sortie jusqu'à l'entrée)
 * Si c'est PAS Ok pour un des 2 cotés, alors on les redéconnecte les 2, et on les reconnecte dans le sens initial, puis on reconnecte tous les maillon dans le sens initial.
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

    stack<Pipeline *> pilePipeline{};

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
        premierMaillon->deconnecterStructure(saveEntreePipeline);
    }

    /**************** SORTIE *******************/
    // Push du premier maillon dans la pile pour le traitement
    pilePipeline.push(premierMaillon);

    // Parcours le chemin depuis sortie jusqu'a fin pipeline
    while (curseurPipeline != nullptr &&
           curseurPipeline->getASortie() == true &&
           typeid(*(curseurPipeline->getSortie())) == typeid(Pipeline))
    {
        // Récupération de la sortie
        precPipeline = curseurPipeline;
        curseurPipeline = (Pipeline *)curseurPipeline->getSortie();

        // Enregistrement du maillon du pipeline
        pilePipeline.push(curseurPipeline);
        // Deconnexion de l'entrée
        precPipeline->deconnecterStructure(curseurPipeline);
    }
    // Marquage du dernier maillon
    dernierMaillon = pilePipeline.top();

    // Marquage du batiment en sortie
    if (dernierMaillon != nullptr) // Normalement pas besoin
    {
        // A un batiment en sortie
        if (dernierMaillon->getASortie())
            saveSortiePipeline = dernierMaillon->getSortie();
        else // A pas de batiment en sortie
            saveSortiePipeline = nullptr;

        // Déconnecte le batiment en sortie si yen a un
        dernierMaillon->deconnecterStructure(saveSortiePipeline);
    }
    /************* TEST INVERSION POSSIBLE *************/
    bool inverserSortie = true;
    bool inverserEntree = true;

    // Yavait un batiment en entrée
    cerr << "saveEntreePipeline : " << saveEntreePipeline << endl;
    if (saveEntreePipeline != nullptr)
    { // premierMaillon -> bat
        inverserEntree = saveEntreePipeline->connecterStructure(premierMaillon, false, false);
    }

    // Yavait un batiment en sortie
    cerr << "saveSortiePipeline : " << saveSortiePipeline << endl;
    if (saveSortiePipeline != nullptr)
    { // bat -> dernierMaillon
        inverserSortie = saveSortiePipeline->connecterStructure(dernierMaillon, true, false);
    }

    // Inverse tout si possible
    if (inverserEntree && inverserSortie)
    {
        // Connexion dans le sens inverse
        while ((int)pilePipeline.size() > 1)
        { // bat -> dernierMaillon ... -> premierMaillon -> bat
            curseurPipeline = pilePipeline.top();
            pilePipeline.pop();

            cerr << curseurPipeline->connecterStructure(pilePipeline.top(), true) << endl;
        }
    }
    else
    {
        // ReDeconnexion des entrée et sortie
        premierMaillon->deconnecterStructure(saveEntreePipeline);
        dernierMaillon->connecterStructure(saveSortiePipeline, true);

        // ReConnexion dans le d'avant sens
        while (pilePipeline.size() > 1)
        { // bat <- dernierMaillon ... <- premierMaillon <- bat
            precPipeline = curseurPipeline;
            curseurPipeline = pilePipeline.top();
            pilePipeline.pop();

            curseurPipeline->connecterStructure(pilePipeline.top(), false);
        }

        // premierMaillon <- bat
        premierMaillon->connecterStructure(saveEntreePipeline, false);
        // bat <- dernierMaillon
        dernierMaillon->connecterStructure(saveSortiePipeline, true);
    }

    // Retourne le résultat si le pipeline a été inversé
    return inverserEntree && inverserSortie;
}
