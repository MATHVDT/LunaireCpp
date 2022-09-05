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

typedef struct Formule
{
    long reactifs; // concatBin
    TYPE_RESSOURCE produit;
} Formule_t;

typedef struct Craft
{
    std::size_t batiment;
    list<Formule *> *formule;
} Craft_t;

extern list<Craft *> *listCrafts;
extern string cheminFichierCrafts;

void initCrafts(string fichierCheminCrafts);
list<Formule *> *lectureFormule(string fichierFormule);

list<TYPE_RESSOURCE> formulePossible(size_t hash, queue<TYPE_RESSOURCE> stock);

long concatBin();

#endif