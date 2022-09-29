#include <iostream>
#include <typeinfo>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <map>

/*
clear && g++ main.cpp -o prog.exe -g && ./prog.exe
*/

using namespace std;

typedef struct eltReaction
{
    int ress;
    int qte;
    bool produit;
} eltReaction_t;

typedef struct envReaction
{
    int batiment;
    string nomBatiment;
    int ress;
    ulong hashRecette;
} envReaction_t;

void lectureDonnees(string cheminFichierLecture,
                    int &nbRessource, map<string, int> &nomsRessource,
                    int &nbTypeBatiment, map<string, int> &nomsTypeBatiment,
                    list<list<eltReaction_t>> &livreCuisine,
                    list<envReaction_t> &listEnvReaction);

void ecritureDonnees(string cheminFichierEcritureFormule,
                     int &nbRessource, map<string, int> &nomsRessource,
                     int &nbTypeBatiment, map<string, int> &nomsTypeBatiment,
                     list<list<eltReaction_t>> &livreCuisine,
                     list<envReaction_t> &listEnvReaction);

void affichageMap(const map<string, int> &map, string nom, bool withEndl = false);
void affichageRecette(const list<eltReaction_t> listRecette);
void affichageEnv(const list<envReaction_t> &listEnvReaction, bool withEndl = false);

ulong concatBinListRessource(const list<int> &combiRessources);

string dossierRessultat = "./crafts";

int main()
{

    string cheminFichierLecture = "./Crafts.txt";
    string cheminFichierEcritureFormule = "./formuleCraft.txt";

    int nbRessource;
    int nbTypeRessource;

    map<string, int> nomsRessource;
    map<string, int> nomsTypeBatiment;

    list<list<eltReaction_t>> livreCuisine; // 📔
    list<envReaction_t> listEnvReaction;

    lectureDonnees(cheminFichierLecture,
                   nbRessource, nomsRessource,
                   nbTypeRessource, nomsTypeBatiment,
                   livreCuisine,
                   listEnvReaction);

    ecritureDonnees(cheminFichierEcritureFormule,
                    nbRessource, nomsRessource,
                    nbTypeRessource, nomsTypeBatiment,
                    livreCuisine,
                    listEnvReaction);

    return 0;
}

/***********************************************************************************************/
/***********************************************************************************************/

void lectureDonnees(string cheminFichierLecture,
                    int &nbRessource, map<string, int> &nomsRessource,
                    int &nbTypeBatiment, map<string, int> &nomsTypeBatiment,
                    list<list<eltReaction_t>> &livreCuisine,
                    list<envReaction_t> &listEnvReaction)
{

    ifstream monFluxLecture;
    monFluxLecture.open(cheminFichierLecture);

    string val, nomBatiment;
    int indiceBatiment;
    int produit, reactif, qte;
    eltReaction_t troupleTmp;
    envReaction_t envReact;
    list<int> listReactifRecette;

    list<eltReaction_t> listRecette; // 📜

    if (monFluxLecture)
    {
        cout << "LECTURE du fichier des crafts : " << cheminFichierLecture << endl;

        /************ Lecture 1ere ligne ************/
        // Lecture case "NB_RESSOURCES" (A1)
        monFluxLecture >> val;
        // Lecture du nombre de ressource (A2)
        monFluxLecture >> nbRessource;
        // Lit chaque nom de Ressource (C1:AV)
        for (int i = 0; i < nbRessource; ++i)
        {
            monFluxLecture >> val;
            nomsRessource.insert(pair<string, int>(val, i));
        }
        // affichageMap(nomsRessource, "nomsRessource", true);

        /************ Lecture 2eme ligne ************/
        // Lecture case "TYPE_BATIMENT" (A2)
        monFluxLecture >> val;
        // Lecture du nombre de ressource (A2)
        monFluxLecture >> nbTypeBatiment;
        // Lit chaque nom de Ressource (C2:K)
        // Commence à -1 car premiere structure est : AucunStructure = -1
        for (int i = -1; i < nbTypeBatiment - 1; ++i)
        {
            monFluxLecture >> val;
            nomsTypeBatiment.insert(pair<string, int>(val, i));
        }
        // affichageMap(nomsTypeBatiment, "nomsTypeBatiment", true);

        /************ Lecture 3eme ligne ************/
        // SKIP première ligne du tableau des crafts
        // Batiment de craft (A3) + RESSOURCE (B3) + nbRessource
        for (int i = 0; i < nbRessource + 2; ++i)
        {
            monFluxLecture >> val;
        }

        /************** Lecture de toutes les recettes *******************/
        // Pour chaque Ressource
        for (int i = 0; i < nbRessource; ++i)
        {
            // Nettoyage de la recette et reactifs precedents
            listRecette.clear();
            listReactifRecette.clear();

            // Récupère le nom du batiment de craft
            monFluxLecture >> nomBatiment;

            monFluxLecture >> val; // Skip du nom du produit
            produit = i;           // Récupération du numéro du produit

            for (int k = 0; k < nbRessource; ++k)
            {                          // Pour chaque potentiel reactif
                monFluxLecture >> qte; // Lecture de la quantite
                if (qte > 0)           // Est un reactif
                {
                    troupleTmp.ress = k;
                    troupleTmp.qte = qte;
                    troupleTmp.produit = false;
                    listRecette.push_back(troupleTmp);              // Ajout à la recette
                    listReactifRecette.push_front(troupleTmp.ress); // Ajout à la liste des reactifs
                }
            }

            // Ajout produit à la recette
            troupleTmp.ress = produit;
            if (listRecette.size() > 0)
            {
                troupleTmp.qte = 1; // Est craftable
                troupleTmp.produit = true;

                // Ajout de l'env de craft
                // Batiment ou la ressource peut etre crafté avec le hash associé
                envReact.batiment = nomsTypeBatiment[nomBatiment];
                envReact.nomBatiment = nomBatiment;
                envReact.ress = produit;
                // Calcul du hash associé au produit avec la liste des reactifs
                envReact.hashRecette = concatBinListRessource(listReactifRecette);
                listEnvReaction.push_back(envReact);
            }
            else
            {
                // cout << "Pas craftable et bat = " << nomBatiment << " pour ressource : " << produit << endl;
                troupleTmp.qte = 0;         // N'est PAS craftable
                troupleTmp.produit = false; // N'est PAS craftable
            }
            // Ajout du produit en tête de recette
            listRecette.push_front(troupleTmp);

            // affichageRecette(listRecette);

            // Ajout de la recette au livre de Cuisine
            livreCuisine.push_back(listRecette);
        }

        // affichageEnv(listEnvReaction, true);
        // affichageMap(nomsRessource,"ress", true);

        monFluxLecture.close();
    }
    else
    {
        std::cerr << "/!\\ Erreur d'ouverture du fichier : " << cheminFichierLecture << "/!\\" << endl;
    }
}

/***********************************************************************************************/
/***********************************************************************************************/

void ecritureDonnees(string cheminFichierEcritureFormule,
                     int &nbRessource, map<string, int> &nomsRessource,
                     int &nbTypeBatiment, map<string, int> &nomsTypeBatiment,
                     list<list<eltReaction_t>> &livreCuisine,
                     list<envReaction_t> &listEnvReaction)
{
    ofstream monFluxEcriture;
    monFluxEcriture.open(cheminFichierEcritureFormule);

    // Tableau des flux/fichier des crafts possibles dans les batiments
    ofstream *fluxFichierCraftBat = new ofstream[nbTypeBatiment];
    string nomFichier;
    bool allOpen = true;
    // Récupération des noms des batiments et overture des flux
    for (auto &p : nomsTypeBatiment)
    {
        if (!fluxFichierCraftBat[p.second])
        {
            allOpen = false;
        }
        nomFichier = dossierRessultat + "/craft" + p.first + ".txt";
        fluxFichierCraftBat[p.second].open(nomFichier);
    }

    if (monFluxEcriture && allOpen)
    {
        /********* Ecriture de toutes les recettes des crafts **************/
        cout << "ECRITURE des Recettes de craft dans le fichier : " << cheminFichierEcritureFormule << endl;
        cout << "ECRITURE craft / BAT dans les fichiers : " << endl;
        for (auto &s : nomsTypeBatiment)
        {
            cout << dossierRessultat << "/craft" << s.first << ".txt" << endl;
        }

        // Ecrit le nb de ressources et donc de lignes dans le fichier
        monFluxEcriture << nbRessource << endl;

        for (auto recette : livreCuisine)
        {
            // Ecriture du nombre d'ingrédients de la recette
            for (auto t : recette)
            { // Ecriture des ingrédients avec les qtés requises
                monFluxEcriture << t.ress << " ";
                monFluxEcriture << t.qte << " ";
                monFluxEcriture << t.produit << " ";
            }
            monFluxEcriture << endl;
        }
        monFluxEcriture.close();

        /********* Ecriture des crafts dispo dans les Batiment **************/
        int *nbCraftBatiment = new int[nbTypeBatiment]{0};
        // Comptage du nombre de crafts par batiment
        for (auto &env : listEnvReaction)
        {
            nbCraftBatiment[env.batiment]++;
        }

        // Ecriture du nb de Crafts par batiment dans les fichiers
        for (int k = 0; k < nbTypeBatiment; ++k)
        {
            fluxFichierCraftBat[k] << nbCraftBatiment[k] << endl;
        }

        // Ecriture des correspondance ress / hash
        for (auto &env : listEnvReaction)
        {
            fluxFichierCraftBat[env.batiment] << env.ress << " ";
            fluxFichierCraftBat[env.batiment] << env.hashRecette;
            fluxFichierCraftBat[env.batiment] << endl;
        }

        // Fermeture des flux
        for (int k = 0; k < nbTypeBatiment; ++k)
        {
            fluxFichierCraftBat[k].close();
        }
        // Libération des new
        delete[] fluxFichierCraftBat;
        delete[] nbCraftBatiment;
    }
    else
    {
        std::cerr << "/!\\ Erreur d'écriture du fichier : " << cheminFichierEcritureFormule << "/!\\" << endl;
    }
}

/***********************************************************************************************/
/***********************************************************************************************/

void affichageMap(const map<string, int> &map, string nom, bool withEndl)
{
    cout << "Affichage d'un map " << nom << " : " << endl;
    for (auto &c : map)
    {
        cout << "(" << c.second << ", " << c.first << ") ";
        if (withEndl)
            cout << endl;
    }
    cout << endl;
}

void affichageRecette(const list<eltReaction_t> listRecette)
{
    // Affichage recette
    cout << "Recette : ";
    for (auto &c : listRecette)
    {
        cout << "(" << c.ress << ", " << c.qte << ", " << c.produit << ") ";
    }
    cout << endl;
}

void affichageEnv(const list<envReaction_t> &listEnvReaction, bool withEndl)
{
    for (auto &e : listEnvReaction)
    {
        cout << "(" << e.batiment << ", " << e.ress << ", " << e.hashRecette << ") ";
        if (withEndl)
            cout << endl;
    }
    cout << endl;
}

/***********************************************************************************************/
/***********************************************************************************************/

ulong concatBinListRessource(const list<int> &combiRessources)
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
    }

    return valConcatBin;
}