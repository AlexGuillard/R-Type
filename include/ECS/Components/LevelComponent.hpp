/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** LevelComponent.hpp
*/

#include <iostream>
#pragma once

namespace ECS::Components {
    /**
    * @brief Component that contains the gravity details
    * @param level in int level of the entity
    */
    struct LevelComponent {
        int level;
    };
}
