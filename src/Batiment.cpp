/**
 * @file Batiment.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implémentation des méthodes de la classe Batiment
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 */
#include "Batiment.hpp"

uint Batiment::_nbBatiments = 0;
uint Batiment::_idMaxBatiments = 0;

Batiment::Batiment()
    : _idBatiment(++_idMaxBatiments)
{
    _nbBatiments++;
    cerr << "Batiment() = default, id : " << _idBatiment << endl;
}

/**
 * @brief Construct a new Batiment:: Batiment object
 *
 * @param Vector2f - *pos*
 * @param Texture* - *texture*
 */
Batiment::Batiment(const Vector2u &pos, Texture *text)
    : Structure{pos, text},
      _idBatiment(++_idMaxBatiments),
      _isFormuleCraftDefine(false),
      _listRessCraftPossible(),
      _formuleCraft(nullptr),
      _stockInterne()
{
    _nbBatiments++;
    cerr << "Batiment(), id : " << _idBatiment << endl;
}

Batiment::~Batiment()
{
    _nbBatiments--;
    cerr << "~Batiment(), id : " << _idBatiment << endl;
}

void Batiment::init() {}

/*******************************************************/

void Batiment::chargerMemoireBatiments()
{
    // Mine::chargerMemoireMines();
    // chargerMemoire Autres Batiment
}

void Batiment::dechargerMemoireBatiments()
{
    // Mine::dechargerMemoireMines();
    // dechargerMemoire Autres Batiment
}

/*******************************************************/

void Batiment::dessiner(float scaleSprite)
{
    Structure::dessiner(scaleSprite);
}

void Batiment::update()
{
    Structure::update();
}

void Batiment::process()
{
    Structure::process();

    if (_isFormuleCraftDefine)
    {
        transfertStockConnexionToInterne();

        if (crafter())
        {
            cerr << "Ressource crafté" << endl;
        }
    }
}

/*******************************************************/

/**
 * @brief Check si la connexion entre le Batiment et une autre strucutre est possible (nb de connexion)
 *
 * @details Dans la méthode override, on regarde si la structrures peut avoir une connexion suplémentaire (sortie ou entrée). Puis dans la méthode Structure::checkConnexionPossible, on regarde si c'est la structure que l'on veut ajouter qui peut accepeter une connexion supplémentaire (entrée ou sortie).
 *
 * @param Structure * - *s*
 * @param bool - *commeSortie*
 *
 * @return true - *Connexion possible*
 * @return false - *Connexion impossible*
 */
bool Batiment::checkConnexionPossible(Structure *s, bool commeSortie)
{
    // Vérifier la compatibilité des structures connectées
    if (typeid(*s) != typeid(Pipeline))
    {
        cerr << "Pas un pipeline que l'on co a ce batiement" << endl;
        return false; // Co à autre chose que pipeline
    }
    return Structure::checkConnexionPossible(s, commeSortie);
}

bool Batiment::updateOrientation()
{
    // Rien
    return false;
}

/**
 * @brief Si le batiment n'est pas parametré pour craft, alors on récupère la liste des ce qui est craftable avec les ressources en _stockEntree.
 *
 * @return list<TYPE_RESSOURCE> *
 */
list<TYPE_RESSOURCE> *Batiment::checkCraftPossible()
{
    if (!_isFormuleCraftDefine)
    {
        // size_t hash = typeid(this).hash_code();
        list<TYPE_RESSOURCE> list = craftPossible(this, _stockConnexion);
        swap(list, _listRessCraftPossible);
    }
    // cerr << " nb _listRessCraftPossible : " << _listRessCraftPossible.size() << endl;
    // cerr << " taille stockEntree : " << _stockEntree.size() << endl;
    // cerr << endl;
    return &_listRessCraftPossible;
}

/**
 * @brief Set la formule des crafts du batiment.
 *
 * @param TYPE_RESSOURCE - *ressCraft*
 */
void Batiment::setFormuleCraft(TYPE_RESSOURCE ressCraft)
{
    if (!_isFormuleCraftDefine)
    {
        // Stockage formule
        _formuleCraft = listFormulesCraft.at((short)ressCraft);
        _isFormuleCraftDefine = true;

        // Vide le stock interne
        _stockInterne.clear();

        for (auto c : *_formuleCraft)
        { // Reactifs
            if (c->produit == false)
            { // Definit le stock interne à 0
                _stockInterne.emplace(c->composant, 0);
            }
        }

        // Texture
        setTextureRessourceCraft(ressCraft);
    }
}

/**
 * @brief Supprime la formule de craft du batiment et nettoye le stock interne.
 *
 */
void Batiment::resetFormuleCraft()
{
    if (!_isFormuleCraftDefine)
    {
        cerr << "Reset d'une formule de craft alors que pas def" << endl;
    }
    _formuleCraft = nullptr;
    _isFormuleCraftDefine = false;
    _stockInterne.clear();
}

/**
 * @brief Vide le stock interne, ie met toutes les quantitées à 0.
 *
 */
void Batiment::videStockInterne()
{
    for (auto r : _stockInterne)
    {
        r.second = 0;
    }
}

/**
 * @brief Indique si le stock interne comporte assez de réactifs pour pouvoir crafter.
 * @details Somme tous les quantités de réactifs nécessaire - la quantité de réactifs présent.
 * La ressource produite est pas prise en compte avec :
 * *(1 - c->produit) *(= 1 => réactif, = 1 => produit)*
 *
 * @return true - *Ya les bonnes quantités*
 * @return false - *Ya PAS les bonnes quantités*
 */
bool Batiment::isQuantiteReactifsOk() const
{
    uint ok = 0;
    for (auto c : *_formuleCraft)
    {
        // cbIlEnFaut - cbYenA * (1 - estProduit)
        ok += c->quantite - _stockInterne.at(c->composant) * (1 - c->produit);
    }
    return ok == 0;
}

/**
 * @brief Transfert les ressources du stockConnexion au stockInterne si c'est possible.
 *
 */
void Batiment::transfertStockConnexionToInterne()
{ // Pour chaque stockConnexion
    for (auto &r : _stockConnexion)
    { // Si elle s'ajoute bien au stockInterne
        if (ajouterStockInterne(r))
        { // On l'enleve du stockConnexion
            r = TYPE_RESSOURCE::Rien;
        }
    }
}

/**
 * @brief Essaye d'ajouter au stock une ressource.
 *
 * @param TYPE_RESSOURCE - *ress*
 * @return true - *Ajout au stock interne*
 * @return false - *Ressource pas dans le stock interne, ou qte nécessaire atteinte*
 */
bool Batiment::ajouterStockInterne(TYPE_RESSOURCE ress)
{

    auto searchStockInterne = _stockInterne.find(ress);

    if (searchStockInterne == _stockInterne.end())
    { // Pas de case dans stockInterne => pas in formule
        return false;
    }

    uint qteNecessaire = 0;
    uint &qteStockInterne = (*searchStockInterne).second;

    for (auto c : *_formuleCraft)
    {
        if (c->composant == ress)
        {
            qteNecessaire = c->quantite;
            if (qteStockInterne < qteNecessaire)
            {
                qteStockInterne++;
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Craft la ressource si possible.
 *
 * @details Verifie qu'il ya bien une sortie et de la place dans le stock de sortie, qu'il ya bien les bonnes qte de ressources. Puis vide le stock Interne et place la ressource produite dans la stockConnexion de sortie.
 *
 * @return true - *Ressource produite*
 * @return false - *Ressource NON produite*
 */
bool Batiment::crafter()
{
    connexion_t *connexionSortie = getConnexionSortie();
    DIRECTION dirSortie;

    if (connexionSortie == nullptr)
        return false; // Pas de sortie
    else
        dirSortie = connexionSortie->direction;

    if (_stockConnexion[(short)dirSortie] != TYPE_RESSOURCE::Rien)
    { // Pas de place en sortie
        return false;
    }

    if (isQuantiteReactifsOk())
    { // Qte ok pour craft
        // Consomme les ressources
        videStockInterne();
        // Produit la ressource
        _stockConnexion[(short)dirSortie] = (*_formuleCraft->begin())->composant;

        // Test de verif 1elt formule = produit
        if (!(*_formuleCraft->begin())->produit)
            cerr << "PB 1elt formule pas un produit" << endl;

        return true;
    }
    return false;
}

void Batiment::remplirStock()
{
    return Structure::remplirStock();
}
TYPE_RESSOURCE Batiment::livrerStock()
{
    return Structure::livrerStock();
}
