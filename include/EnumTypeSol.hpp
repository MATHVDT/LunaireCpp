/**
 * @file EnumTypeSol.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Enum class les différents types de sol
 * @version 0.1
 * @date 2022-06-09
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef __ENUM_TYPE_SOL_HPP__
#define __ENUM_TYPE_SOL_HPP__

#define NB_SOL 5;

enum class TYPE_SOL
{
    Vierge,
    Trou,
    Montage,
    GisementOr,
    GisementFer,
};

#endif