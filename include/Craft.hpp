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

#include "EnumTypeRessource.hpp"
#include "Mine.hpp"
#include "Fonderie.hpp"

using namespace std;

typedef struct ReactifsProduitCraft
{
    long reactifs; // concatBin
    TYPE_RESSOURCE produit;
} ReactifsProduitCraft_t;

typedef struct Craft
{
    std::size_t batiment;
    list<ReactifsProduitCraft_t *> *formule;
} Craft_t;

typedef struct ComposantCraft
{
    TYPE_RESSOURCE composant;
    uint quantite;
    bool produit;
} ComposantCraft_t;

extern list<Craft_t *> *listCrafts;
extern string cheminFichierCrafts;
extern vector<list<ComposantCraft *>> listFormulesCraft;

void initCrafts(string fichierCheminCrafts = cheminFichierCrafts);
list<ReactifsProduitCraft *> *lectureReactifsProduitCraft(string fichierFormule);

void initFormulesCraft(string fichierFormuleCraft = "ressource/crafts/formuleCraft.txt");

list<TYPE_RESSOURCE> formulePossible(size_t hash, queue<TYPE_RESSOURCE> stock);

long concatBin();

#endif