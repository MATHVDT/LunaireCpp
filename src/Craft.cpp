/**
 * @file Craft.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Fichier définissant les Crafts
 *
 * @version 0.1
 * @date 2022-09-05
 *
 * @copyright Copyright (c) 2022
 */
#include "Craft.hpp"

string cheminFichierCrafts = "";
extern list<Craft *> *listCrafts = new list<Craft *>{};

/**
 * @brief Remplit la list des crafts
 *
 * @param string - *fichierCheminCrafts*
 */
void initCrafts(string fichierCheminCrafts)
{
    // uint nbBatiment = 6;
    // string batimentNom[nbBatiment] =
    //     {"Mine", "Fonderie",
    //      "Fabrique", "Atelier",
    //      "Cuve", "ChantierSpatial"};

    // size_t batimentHash[nbBatiment] =
    //     {typeid(Mine).hash_code(),
    //      typeid(Fonderie).hash_code(),
    //      typeid(Fabrique).hash_code(),
    //      typeid(Atelier).hash_code(),
    //      typeid(Cuve).hash_code(),
    //      typeid(ChantierSpatial).hash_code()};

    uint nbBatiment = 2;
    string batimentNom[nbBatiment] =
        {"Mine", "Fonderie"};

    size_t batimentHash[nbBatiment] =
        {typeid(Mine).hash_code(),
         typeid(Fonderie).hash_code()};

    Craft_t *craftTmp = nullptr;
    list<Formule_t *> *listFormules = nullptr;
    string fichierCraft;

    ifstream monFlux;
    monFlux.open(fichierCheminCrafts);
    if (monFlux)
    {
        for (uint k = 0; k < nbBatiment; + k)
        {
            cerr << "Chargement des crafts : " << batimentNom[k] << ", hash_code : " << batimentHash[k] << endl;

            craftTmp = (Craft_t *)malloc(sizeof(Craft_t));

            // Chemin du fichier contenant les crafts
            monFlux >> fichierCraft;
            cerr << fichierCraft << endl;

            listFormules = lectureFormule(fichierCraft);

            craftTmp->batiment = batimentHash[k];
            craftTmp->formule = listFormules;

            listCrafts->emplace_back(craftTmp);

            monFlux.close();
        }
    }
    else
    {
        std::cerr << "/!\\ Erreur d'ouverture du fichier : " << fichierCheminCrafts << " /!\\" << endl;
    }
}

/**
 * @brief Remplit les formules des crafts
 *
 * @param string - *fichierFormule*
 * @return list<Formule *>* - *listFormules*
 */
list<Formule *> *lectureFormule(string fichierFormule)
{
    int nbFormules = 0;
    list<Formule_t *> *listFormules = new list<Formule *>{};
    Formule_t *f;
    long reactifs;
    int produitInt;
    TYPE_RESSOURCE produit;

    ifstream monFlux;
    monFlux.open(fichierFormule);
    if (monFlux)
    {
        monFlux >> nbFormules;

        for (uint i = 0; i < nbFormules; ++i)
        {
            f = new Formule_t{};
            monFlux >> reactifs;
            monFlux >> produitInt;
            produit = static_cast<TYPE_RESSOURCE>(produitInt);
            f->reactifs = reactifs;
            f->produit = produit;
            listFormules->push_back(f);
        }
        monFlux.close();
    }
    else
    {
        std::cerr << "/!\\ Erreur d'ouverture du fichier : " << fichierFormule << " /!\\" << endl;
    }
    return listFormules;
}

/**
 * @brief Donne la liste des ressources craftables
 *
 * @param size_t hash - *hash_code des structures*
 * @param queue<TYPE_RESSOURCE> stockEntree
 * @return list<TYPE_RESSOURCE>
 */
list<TYPE_RESSOURCE> formulePossible(size_t hash, queue<TYPE_RESSOURCE> stock)
{

    list<TYPE_RESSOURCE> listRessCraft{};

    while (!stock.empty())
    {
        listRessCraft.push_back(stock.front());
        stock.pop();
    }

    // Garder uniquement le type (pas les qte)
    sort(listRessCraft.begin(), listRessCraft.end());
    unique(listRessCraft.begin(), listRessCraft.end());
    // while (listRessCraft.size() < 5)
    // {
    //     listRessCraft.emplace_front(TYPE_RESSOURCE::Rien);
    // }


    for (Craft_t *c : *listCrafts)
    {
        if (c->batiment == hash)
        {
        }
    }
}
