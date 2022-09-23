/**
 * @file Craft.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Fichier entete pour les structures des Crafts
 *
 * @version 0.1
 * @date 2022-09-05
 *
 * @copyright Copyright (c) 2022
 */
#ifndef __CRAFT_HPP__
#define __CRAFT_HPP__

#include <cstddef>
#include <iostream>
#include <string>
#include <cstring>
#include <typeinfo>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <list>
#include <vector>

#include "EnumTypeRessource.hpp"
#include "EnumTypeStructure.hpp"
#include "Structure.hpp"
// #include "Mine.hpp"
// #include "Fonderie.hpp"

using namespace std;

typedef struct ReactifsProduitCraft
{
    ulong reactifs; // concatBin
    TYPE_RESSOURCE produit;
} ReactifsProduitCraft_t;

typedef struct CraftBatiment
{
    std::size_t batiment;
    list<ReactifsProduitCraft_t *> *formule;
} CraftBatiment_t;

typedef struct FormuleCraft
{
    TYPE_RESSOURCE composant;
    uint quantite;
    bool produit;
} FormuleCraft_t;

extern string cheminFichierCrafts;

// VARIABLE
extern list<CraftBatiment_t *> listCraftsBatiment;
extern vector<list<FormuleCraft_t *> *> listFormulesCraft;

void initCrafts(string fichierCheminCrafts = cheminFichierCrafts);
list<ReactifsProduitCraft *> *lectureReactifsProduitCraft(string fichierFormule);

void initFormulesCraft(string fichierFormuleCraft = "ressource/crafts/formuleCraft.txt");

void deleteCraft();

void afficherFormuleCraft(ostream &monFlux = cout);

list<TYPE_RESSOURCE> craftPossible(Structure *s,
                                   TYPE_RESSOURCE stock[6]);
list<TYPE_RESSOURCE> craftPossible(const size_t hash,
                                   TYPE_RESSOURCE stock[6]);

void combinate(vector<TYPE_RESSOURCE> e,
               int perm[], int index, int n, int k,
               list<TYPE_RESSOURCE> *tabList,
               int &curseurLigne);

ulong concatBinListRessource(const list<TYPE_RESSOURCE> &combiRessources);

/***************************************************/
/*                 Fonctions inline                */
/***************************************************/


#endif