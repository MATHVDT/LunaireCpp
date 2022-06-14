#ifndef __CORRESPONDANCE_HPP__
#define __CORRESPONDANCE_HPP__

#include "EnumTypeRessource.hpp"
#include "EnumTypeStructure.hpp"
#include "EnumTypeSol.hpp"

TYPE_RESSOURCE typeSolToTypeRessource(TYPE_SOL sol);
TYPE_RESSOURCE typeStructureToTypeRessource(TYPE_STRUCTURE structure);
TYPE_STRUCTURE typeStructureToTypeRessource(TYPE_RESSOURCE ressource);

#endif