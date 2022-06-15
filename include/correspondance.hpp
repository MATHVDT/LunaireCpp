#ifndef __CORRESPONDANCE_HPP__
#define __CORRESPONDANCE_HPP__

#include "EnumTypeRessource.hpp"
#include "EnumTypeStructure.hpp"
#include "EnumTypeSol.hpp"

TYPE_RESSOURCE typeSolToTypeRessource(TYPE_SOL sol);

TYPE_RESSOURCE typeStructureToTypeRessource(TYPE_STRUCTURE structure);
TYPE_RESSOURCE typeMineToTypeRessource(TYPE_STRUCTURE structure);
TYPE_RESSOURCE typeUsineToTypeRessource(TYPE_STRUCTURE structure);


TYPE_STRUCTURE typeRessourceToTypeStructure(TYPE_RESSOURCE ressource);
TYPE_STRUCTURE typeRessourceToTypeMine(TYPE_RESSOURCE ressource);
TYPE_STRUCTURE typeRessourceToTypeUsine(TYPE_RESSOURCE ressource);


#endif