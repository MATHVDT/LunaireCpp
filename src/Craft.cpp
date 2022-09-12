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

list<CraftBatiment_t *> listCraftsBatiment{};
// list<CraftBatiment_t *> *listCraftsBatiment = new list<CraftBatiment *>{};
vector<list<FormuleCraft *> *> listFormulesCraft;

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

    // size_t batimentHash[nbBatiment] =
    //     {typeid(Mine).hash_code(),
    //      typeid(Fonderie).hash_code()};

    CraftBatiment_t *craftTmp = nullptr;
    list<ReactifsProduitCraft_t *> *listFormules = nullptr;
    string fichierCraft;

    ifstream monFlux;
    monFlux.open(fichierCheminCrafts);
    if (monFlux)
    {
        // Chargement des formules des crafts
        monFlux >> fichierCraft;
        initFormulesCraft(fichierCraft);

        // Chargement des crafts possibles par batiment
        for (uint k = 0; k < nbBatiment; ++k)
        {
            cerr << "Chargement des crafts : " << batimentNom[k] << endl;
            // ", hash_code : " << batimentHash[k] << endl;

            craftTmp = new CraftBatiment_t{};

            // Chemin du fichier contenant les crafts
            monFlux >> fichierCraft;
            cerr << "Fichier craft est : " << fichierCraft << endl;

            listFormules = lectureReactifsProduitCraft(fichierCraft);

            // craftTmp->batiment = batimentHash[k];
            craftTmp->formule = listFormules;

            listCraftsBatiment.emplace_back(craftTmp);
        }
        monFlux.close();
    }
    else
    {
        std::cerr << "/!\\ Erreur d'ouverture du fichier : " << fichierCheminCrafts << " /!\\" << endl;
    }
}

/**
 * @brief Remplit les formules des crafts a partir du fichier correspondant
 *
 * @param string - *fichierFormule*
 * @return list<ReactifsProduitCraft *>* - *listFormules*
 */
list<ReactifsProduitCraft *> *lectureReactifsProduitCraft(string fichierFormule)
{
    int nbFormules = 0;
    list<ReactifsProduitCraft_t *> *listFormules = new list<ReactifsProduitCraft *>{};
    ReactifsProduitCraft_t *f;
    ulong reactifs;
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
    FormuleCraft_t *composantTmp = nullptr;
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
            listFormulesCraft.push_back(new list<FormuleCraft *>{});
            // Nombre de triplet à lire
            monFlux >> nbElementFormule;
            for (uint i = 0; i < nbElementFormule; ++i)
            {
                composantTmp = new FormuleCraft_t{};
                monFlux >> composantShort;
                composantTmp->composant = static_cast<TYPE_RESSOURCE>(composantShort);
                monFlux >> composantTmp->quantite;
                monFlux >> composantTmp->produit;
                listFormulesCraft.at(k)->push_back(composantTmp);
            }
        }
        monFlux.close();
    }
    else
    {
        std::cerr << "/!\\ Erreur d'ouverture du fichier : " << fichierFormuleCraft << " /!\\" << endl;
    }
}

/*******************************************************/
void deleteCraft()
{
    // // Formule craft
    for (auto list : listFormulesCraft)
    {
        for (auto elt : *list)
        { // Delete des elt dans une formule

            delete elt;
        }
    } // vector delete tout seul car par d'allocation

    // Craft batiment
    auto it2 = listCraftsBatiment.begin();
    while (it2 != listCraftsBatiment.end())
    {
        auto it3 = (*it2)->formule->begin();
        while (it3 != (*it2)->formule->end())
        { // delete ReactifsProduitCraft_t
            delete *it3;
            ++it3;
        }
        // delete list<ReactifsProduitCraft_t *>
        delete (*it2)->formule;
        // delete CraftBatiment_t *
        delete *it2;
        ++it2;
    }
}

/*******************************************************/
/*******************************************************/

/**
 * @brief Affiche les formules des crafts
 *
 * @param ostream & - *monFlux*
 */
void afficherFormuleCraft(ostream &monFlux)
{
    for (int k = 0; k < listFormulesCraft.size(); ++k)
    {
        for (auto c : *listFormulesCraft[k])
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
 *
 * @return list<TYPE_RESSOURCE> - *listProduitsCraftables*
 */
list<TYPE_RESSOURCE> craftPossible(const size_t hash, queue<TYPE_RESSOURCE> stock)
{
    vector<TYPE_RESSOURCE> vectorStock{};
    list<TYPE_RESSOURCE> listProduitsCraftables{};

    /******* Récupère différents types ressources *******/
    // while (!stock.empty())
    // {
    //     if (stock.front() != TYPE_RESSOURCE::Rien)
    //     {
    //         vectorStock.push_back(stock.front());
    //     }
    //     stock.pop();
    // }

    // Garder uniquement le type (pas les qte)
    // Ordre décroissant
    sort(vectorStock.begin(), vectorStock.end(), greater<TYPE_RESSOURCE>());

    vector<TYPE_RESSOURCE>::iterator it = unique(vectorStock.begin(), vectorStock.end());
    vectorStock.resize(distance(vectorStock.begin(), it));

    // Affichage stock ressource unique trié
    /*
    cerr << endl
         << "Affichage stock ressource unique trié" << endl;
    for (auto x : vectorStock)
    {
        cerr << static_cast<short>(x) << " ";
    };
    */

    int n = vectorStock.size();
    int nbCombi = pow(2, n) > 0 ? pow(2, n) - 1 : 0;
    const int nbMaxReactifs = 5;
    static int curseurLigne = 0;
    list<TYPE_RESSOURCE> *tabListCombiCraft =
        new list<TYPE_RESSOURCE>[nbCombi] {};

    /******* Récupère combinaisons possibles *******/
    for (int k = 1; k <= n; ++k)
    {
        int perm[n] = {0};
        combinate(vectorStock, perm, 0, n, k,
                  tabListCombiCraft, curseurLigne);
    }

    // Affichage combinaison
    /*
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
    */

    /****** Récupère liste ressources ******/
    ulong valConcatBin;
    list<ReactifsProduitCraft_t *> *listRessPotentielles = nullptr;

    // Récupération de la liste des ressources
    // potentiellement craftables dans ce batiment
    for (auto craftBat : listCraftsBatiment)
    {
        if (hash == craftBat->batiment)
        {
            listRessPotentielles = craftBat->formule;
            // cerr << "hash trouvé dans listCraftsBatiment" << endl;
            break;
        }
    }
    if (listRessPotentielles == nullptr)
    {
        cerr << "Erreur, le hash du batiment n'a pas été trouvé dans listCraftsBatiment" << endl;
        cerr << "hash pas trouve : " << hash << endl;
    }

    // Utilisation d'une lambda fonction
    // Redéfini le prédicat en fct de valConcatBin
    auto predicatValConcatBin = [&valConcatBin](ReactifsProduitCraft_t *c)
    {
        return c->reactifs == valConcatBin;
    };

    auto itFind = listRessPotentielles->begin();

    // Pour chaque combi :
    for (int i = 0; i < nbCombi; ++i)
    {
        // Récupère valeur concaténer binaire
        // associé à la combinaison de ressources
        valConcatBin = concatBinListRessource(tabListCombiCraft[i]);

        // Check dans la list des ressources
        // potentiellement craftables
        itFind = find_if(listRessPotentielles->begin(), listRessPotentielles->end(), predicatValConcatBin);

        // Trouvé, ie différent du dernier elt
        if (itFind != listRessPotentielles->end())
        { // Ajout du produit craftable
            listProduitsCraftables.push_back((*itFind)->produit);
        }
    }

    return listProduitsCraftables;
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
 * @param const list<TYPE_RESSOURCE> &combiRessources
 * @return ulong - *Valeur concaténer Binaire*
 */
ulong concatBinListRessource(const list<TYPE_RESSOURCE> &combiRessources)
{
    const short RIEN = 0;
    ulong valConcatBin = 0;
    uint nbRessources = 0;

    for (auto r : combiRessources)
    {
        // Décalage de 2 octets (short)
        valConcatBin = valConcatBin << 16;
        // Concaténation avec un OU logiques
        valConcatBin = valConcatBin | (ulong)r;
        // cout << (ulong)r << " ";
    }
    // cout << endl
    //      << "valeur final : "
    //      << valConcatBin << endl;
    return valConcatBin;
}