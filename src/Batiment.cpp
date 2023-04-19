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

/**
 * @brief Test si la structure est bien un Batiment.
 *
 * @param Structure * - *s*
 * @return true - *Est un Batiment*
 * @return false - *N'est PAS un Batiment*
 */
bool Batiment::isBatiment(Structure *s)
{
    Batiment *isTypeBatiment = dynamic_cast<Batiment *>(s);
    return isTypeBatiment != nullptr;
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
        _isFormuleCraftDefine = true;
        _formuleCraft = listFormulesCraft.at((short)ressCraft);

        // Supprime la liste des crafts possibles
        _listRessCraftPossible.clear();

        // Vide le stock interne
        _stockInterne.clear();

        for (auto c : *_formuleCraft)
        { // Reactifs
          // Definit le stock interne à 0
            _stockInterne.emplace(c->composant, 0);
        }

        // Texture
        setTextureRessourceCraft(ressCraft);

        cerr << "Ressoure crafter dans la mine : " << ressString[ressCraft] << endl;
    }
    else
    {
        cerr << "Erreur formule deja define" << endl;
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
        if (c->produit == false)
        { // cbIlEnFaut - cbYenA
            cout << "cbIlEnFaut : " << c->quantite << " et cvYenA : " << _stockInterne.at(c->composant) << endl;
            ok += c->quantite - _stockInterne.at(c->composant);
        }
    }
    cout << "Reactif calcul total qte : " << ok << endl;
    return (ok == 0);
}

/**
 * @brief Transfert les ressources du stockConnexion au stockInterne si c'est possible.
 *
 */
void Batiment::transfertStockConnexionToInterne()
{ // Pour chaque stockConnexion
    // cerr << "Test de transfer ressrouce Interne" << endl;

    for (uint dir = DIRECTION::NORD;
         dir <= DIRECTION::NORDEST;
         ++dir)
    {
        if (_connexions[dir].type != TypeConnexion::Output)
        { // Si elle s'ajoute bien au stockInterne
            if (ajouterStockInterne(_stockConnexion[dir]))
            { // On l'enleve du stockConnexion
                _stockConnexion[dir] = TYPE_RESSOURCE::Rien;
            }
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
                cout << "Ajout qte Interne : " << (*searchStockInterne).second << endl;
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
    // cout << "Test de craft" << endl;

    connexion_t *connexionSortie = getConnexionSortie();
    DIRECTION dirSortie;

    if (connexionSortie == nullptr)
    {
        cerr << "Pas de sortie pour le craft" << endl;
        return false; // Pas de sortie
    }
    else
    {
        dirSortie = connexionSortie->direction;
    }

    if (_stockConnexion[(short)dirSortie] != TYPE_RESSOURCE::Rien)
    { // Pas de place en sortie
        cerr << "pas de place en sortie pour le craft : " << ressString[_stockConnexion[(short)dirSortie]] << endl;
        return false;
    }

    if (_isFormuleCraftDefine)
    {
        if (isQuantiteReactifsOk())
        { // Qte ok pour craft
            // Consomme les ressources
            videStockInterne();
            // Produit la ressource
            _stockConnexion[(short)dirSortie] = (*_formuleCraft->begin())->composant;

            // Test de verif 1elt formule = produit
            if (!(*_formuleCraft->begin())->produit)
                cerr << "PB 1elt formule pas un produit" << endl;

            cerr << "stock sortie : " << ressString[_stockConnexion[dirSortie]] << endl;
            return true;
        }
        else
        {
            cerr << "Pas assez de réactifs" << endl;
        }
    }
    else
    {
        cerr << "Formule pas defini" << endl;
    }
    return false;
}

void Batiment::remplirStock()
{
    return Structure::remplirStock();
}
