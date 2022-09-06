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

string cheminFichierCrafts = "ressource/crafts/cheminFichierCrafts.txt";

list<Craft_t *> *listCrafts = new list<Craft *>{};
vector<list<ComposantCraft *>> listFormulesCraft;

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
    list<ReactifsProduitCraft_t *> *listFormules = nullptr;
    string fichierCraft;

    ifstream monFlux;
    monFlux.open(fichierCheminCrafts);
    if (monFlux)
    {
        for (uint k = 0; k < nbBatiment; ++k)
        {
            cerr << "Chargement des crafts : " << batimentNom[k] << ", hash_code : " << batimentHash[k] << endl;

            craftTmp = (Craft_t *)malloc(sizeof(Craft_t));

            // Chemin du fichier contenant les crafts
            monFlux >> fichierCraft;
            cerr << "Fichier craft est : " << fichierCraft << endl;

            listFormules = lectureReactifsProduitCraft(fichierCraft);

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
 * @return list<ReactifsProduitCraft *>* - *listFormules*
 */
list<ReactifsProduitCraft *> *lectureReactifsProduitCraft(string fichierFormule)
{
    int nbFormules = 0;
    list<ReactifsProduitCraft_t *> *listFormules = new list<ReactifsProduitCraft *>{};
    ReactifsProduitCraft_t *f;
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
            f = new ReactifsProduitCraft_t{};
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
 * @brief Remplit la list des formules des crafts
 *
 * @param string - *fichierFormuleCraft*
 */
void initFormulesCraft(string fichierFormuleCraft)
{
    ComposantCraft_t *composantTmp = nullptr;
    short composantShort;
    uint nbRessources;
    uint nbElementFormule;

    ifstream monFlux;
    monFlux.open(fichierFormuleCraft);
    string ligne;
    if (monFlux)
    {
        monFlux >> nbRessources;
        for (uint k = 0; k < nbRessources; ++k)
        {
            listFormulesCraft.push_back(list<ComposantCraft *>{});
            // Nombre de triplet à lire
            monFlux >> nbElementFormule;
            for (uint i = 0; i < nbElementFormule; ++i)
            {
                composantTmp = new ComposantCraft_t{};
                monFlux >> composantShort;
                composantTmp->composant = static_cast<TYPE_RESSOURCE>(composantShort);
                monFlux >> composantTmp->quantite;
                monFlux >> composantTmp->produit;
                listFormulesCraft.at(k).push_back(composantTmp);
            }
        }
        monFlux.close();
    }
    else
    {
        std::cerr << "/!\\ Erreur d'ouverture du fichier : " << fichierFormuleCraft << " /!\\" << endl;
    }
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
    // DEfini les operateru des comparaisons type_ressources
    // sort(listRessCraft.begin(), listRessCraft.end());
    // unique(listRessCraft.begin(), listRessCraft.end());
    // while (listRessCraft.size() < 5)
    // {
    //     listRessCraft.emplace_front(TYPE_RESSOURCE::Rien);
    // }
    // ICI les combi possibles

    for (Craft_t *c : *listCrafts)
    {
        if (c->batiment == hash)
        {
        }
    }
}
