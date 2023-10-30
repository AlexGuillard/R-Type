/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** BydoShotComponent
*/

#pragma once

#include <cstddef>

#include "enums.hpp"

namespace ECS::Components {

    /**
     * @brief Component for entities that request the creation of a Bydo shot.
     * Defines the damage, speed, direction and (optionally) the team of the
     * shot.
     * @param damage The damage of the shot.
     * @param speed The speed of the shot (in pixels per second).
     * @param xDirection The x direction of the shot (direction must be
     * normalized).
     * @param yDirection The y direction of the shot (direction must be
     * normalized).
     * @param team The team of the shot (defaults to Enemy).
     */
    struct BydoShotComponent
    {
        std::size_t damage;
        float speed;
        float xDirection;
        float yDirection;
        Enums::TeamGroup team = Enums::TeamGroup::ENEMY;
    };

} // namespace ECS::Components
