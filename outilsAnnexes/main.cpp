#include <iostream>
#include <string>
#include <fstream>
#include <list>

/*
g++ main.cpp -o prog -g && ./prog
*/

using namespace std;

typedef struct trouple
{
    int ress;
    int qte;
    bool produit;
} trouple_t;

int main()
{

    string cheminFichierLecture = "./Crafts.txt";
    string cheminFichierEcriture = "./formuleCraft.txt";

    ifstream monFluxLecture;
    ofstream monFluxEcriture;
    monFluxLecture.open(cheminFichierLecture);
    monFluxEcriture.open(cheminFichierEcriture);

    int nbRessource;
    string val;
    int produit, reactif, qte;
    trouple_t troupleTmp;

    list<trouple_t> listRecette;        // 📜
    list<list<trouple_t>> livreCuisine; // 📔

    if (monFluxLecture && monFluxEcriture)
    {
        // Lecture du nombre de ressource
        monFluxLecture >> nbRessource;

        // Skip de la 2eme ligne (noms ressources)
        for (int i = 0; i < nbRessource + 1; ++i)
        {
            monFluxLecture >> val;
            // cout << val << endl;
        }

        /************** Lecture de toutes les recettes *******************/
        cout << "LECTURE des Recettes de craft dans le fichier : " << cheminFichierLecture << endl;

        // Pour chaque Ressource
        for (int i = 0; i < nbRessource; ++i)
        {
            listRecette.clear();   // Netoyage de la recette precedente
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
                    listRecette.push_back(troupleTmp); // Ajout à la recette
                }
            }

            // Ajout produit à la recette
            troupleTmp.ress = produit;
            if (listRecette.size() > 0)
            {
                troupleTmp.qte = 1; // Est craftable
                troupleTmp.produit = true;
            }
            else
            {
                troupleTmp.qte = 0;         // N'est PAS craftable
                troupleTmp.produit = false; // N'est PAS craftable
            }
            listRecette.push_front(troupleTmp);

            // Ajout de la recette au livre de Cuisine
            livreCuisine.push_back(listRecette);

            // Affichage recette
            // cout << "Recette : " << val << " (indice " << produit << ") : ";
            // for (auto &c : listRecette)
            // {
            //     cout << "(" << c.ress << ", " << c.qte << ", " << c.produit << ") ";
            // }
            // cout << endl;
        }
        monFluxLecture.close();

        /********* Ecriture de toutes les recettes dans le bon format **************/
        cout << "ECRITURE des Recettes de craft dans le fichier : " << cheminFichierEcriture << endl;

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
    }
    else
    {
        std::cerr << "/!\\ Erreur d'ouverture du fichier : " << cheminFichierLecture << " ou du fichier : " << cheminFichierEcriture << "/!\\" << endl;
    }

    return 0;
}
