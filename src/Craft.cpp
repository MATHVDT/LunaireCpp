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
        }
        monFlux.close();
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
 * @brief Remplit la list des formules des crafts dans un vector
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
 * @brief Affiche les formules des crafts
 *
 * @param ostream & - *monFlux*
 */
void afficherFormuleCraft(ostream &monFlux)
{
    for (int k = 0; k < listFormulesCraft.size(); ++k)
    {
        for (auto c : listFormulesCraft[k])
        {
            monFlux << static_cast<int>(c->composant) << " " << c->quantite << " " << c->produit << ", ";
        }
        monFlux << endl;
    }
}

/**
 * @brief Donne la liste des ressources craftables
 *
 * @param size_t hash - *hash_code des structures*
 * @param queue<TYPE_RESSOURCE> stockEntree
 * @return list<TYPE_RESSOURCE>
 */
vector<TYPE_RESSOURCE> CraftPossible(const size_t hash, queue<TYPE_RESSOURCE> &stock)
{
    vector<TYPE_RESSOURCE> vectorStock{};
    list<TYPE_RESSOURCE> listCraftPossible{};

    while (!stock.empty())
    {
        if (stock.front() != TYPE_RESSOURCE::Rien)
        {
            vectorStock.push_back(stock.front());
        }
        stock.pop();
    }

    // Garder uniquement le type (pas les qte)
    // Ordre décroissant
    sort(vectorStock.begin(), vectorStock.end());

    vector<TYPE_RESSOURCE>::iterator it = unique(vectorStock.begin(), vectorStock.end());
    vectorStock.resize(distance(vectorStock.begin(), it));

    // Affichage stock ressource unique trié
    cerr << endl
         << "Affichage stock ressource unique trié" << endl;
    for (auto x : vectorStock)
    {
        cerr << static_cast<short>(x) << " ";
    };

    int n = vectorStock.size();
    int nbCombi = pow(2, n);
    const int nbMaxReactifs = 5;
    static int curseurLigne = 0;
    list<TYPE_RESSOURCE> *tabListCombiCraft =
        new list<TYPE_RESSOURCE>[nbCombi] {};

    // Récupère toutes les combinaisons possibless
    for (int k = 1; k <= n; ++k)
    {
        int perm[n] = {0};
        combinate(vectorStock, perm, 0, n, k,
                  tabListCombiCraft, curseurLigne);
    }

    // Affichage combinaison
    cerr << endl
         << "Affichage combinaison" << endl;
    for (int k = 0; k < nbCombi; ++k)
    {
        for (auto x : tabListCombiCraft[k])
        {
            cerr << static_cast<short>(x) << " ";
        }
        cerr << endl;
    }

    // while (listStock.size() < 5)
    // {
    //     listStock.emplace_front(TYPE_RESSOURCE::Rien);
    // }
    // ICI les combi possibles

    // for (Craft_t *c : *listCrafts)
    // {
    //     if (c->batiment == hash)
    //     {
    //     }
    // }
    return vectorStock;
}

/******************************************************/

/**
 * @brief Donne un tableau contenant toutes les combinaisons possibles d'un ensemble (dans des list<TYPE_RESSOURCE>)
 *
 * @param vector<TYPE_RESSOURCE> a[] : given array of chars
 *
 * @param int perm[] : perm[i] is 1 if a[i] is considered, else 0
 * @param int index : subscript of perm which is to be 0ed and 1ed
 * @param int n : length of the given input array
 * @param int k : length of the permuted string
 *
 * @param list<TYPE_RESSOURCE> *tabList tableau des listes des combi
 * @param int &curseurLigne indicateur pour remplir le tableau
 */
void combinate(vector<TYPE_RESSOURCE> e,
               int perm[], int index, int n, int k,
               list<TYPE_RESSOURCE> *tabList,
               int &curseurLigne)
{
    static int count = 0;
    if (count == k)
    {
        for (int i = 0; i < n; i++)
        {
            if (perm[i] == 1)
            {
                tabList[curseurLigne].push_front(e[i]);
            }
        }
        curseurLigne += 1;
    }
    else if ((n - index) >= (k - count))
    {
        perm[index] = 1;
        count++;
        combinate(e, perm, index + 1, n, k, tabList, curseurLigne);
        perm[index] = 0;
        count--;
        combinate(e, perm, index + 1, n, k, tabList, curseurLigne);
    }
}

/**
 * @brief Concatène les ressources en binaire 
 * @details Ressource de types enum class (short) donc sur 2 octets => concatène 4 ressources => 4 * 2 = 8 octets type ulong pour faire reference à une ressource
 * 
 * @param combiRessources 
 * @return ulong 
 */
ulong concatBinListRessource(const list<TYPE_RESSOURCE> &combiRessources)
{
    const short RIEN = 0;
    ulong valConcatBin;
    uint nbRessources = 0;

    for (auto r : combiRessources)
    {
        // Décalage de 2 octets (short)
        valConcatBin = valConcatBin << 16;
        // Concaténation avec un OU logiques
        valConcatBin = valConcatBin | (long)r;
    }
    return valConcatBin;
}