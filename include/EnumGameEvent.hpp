/**
 * @file EnumGameEvent.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Enum des différents events possible dans le jeu
 * @version 0.1
 * @date 2022-09-03
 *
 * @copyright Copyright (c) 2022
 */
#ifndef __GAME_EVENT_HPP__
#define __GAME_EVENT_HPP__

const int NB_GAME_EVENT = 2;

enum GameEvent
{
    AucunGameEvent,
    InverserSensPipeline,
    PlacerPipeline,
    PlacerMarchand,
    PlacerMine,
    PlacerFonderie,
    PlacerFabrique,
    PlacerAtelier,
    PlacerCuve,
    PlacerChantierSpatial,
    CheckCraftPossible,

    ViderStock,
    Upgrade,
    Detruire,
    ValiderCraft,
    ResetCraft
};

#endif