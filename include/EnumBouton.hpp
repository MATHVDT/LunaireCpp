/**
 * @file EnumBouton.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Enum liés aux boutons
 *
 * @version 0.1
 * @date 2022-08-31
 *
 * @copyright Copyright (c) 2022
 */
#ifndef __BOUTON_ENUM_HPP__
#define __BOUTON_ENUM_HPP__

const uint NB_STATE_BOUTONS = 6;

enum BoutonState
{
    Normal = 0,  // Bouton normale
    Focus = 1,   // Bouton selectionné sans souris (accessibilité)
    Hover = 2,   // Bouton survolé
    Pressed = 3, // Bouton enfoncé avec souris toujours en clic
    Active = 4,  // Bouton activé sans clic de souris
    Disabled = 5 // Bouton désactivé (plus cliquable)
};

const uint NB_BOUTONS = 13;

enum BoutonType
{
    boutonPipeline = 0,
    boutonMarchand = 1,
    boutonMine = 2,
    boutonFonderie = 3,
    boutonFabrique = 4,
    boutonAtelier = 5,
    boutonCuve = 6,
    boutonChantierSpatial = 7,

    boutonValiderCraft = 8,
    boutonResetCraft = 9,
    boutonUpgradeStructure = 10,
    boutonDetruireStructure = 11,
    boutonViderStock = 12
};

#endif