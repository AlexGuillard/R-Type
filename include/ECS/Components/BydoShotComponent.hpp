/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** BydoShotComponent
*/

#pragma once

#include <cstddef>

#include "enums.hpp"
#include "Utils.hpp"

namespace ECS::Components {

    /**
     * @brief Component for entities that request the creation of a Bydo shot.
     * Defines the damage, speed, direction and (optionally) the team of the
     * shot.
     * @param damage The damage of the shot.
     * @param speed The speed of the shot (in pixels per second).
     * @param position The position of the shot.
     * @param direction The direction of the shot. (unit vector)
     * @param team The team of the shot (defaults to Enemy).
     */
    struct BydoShotComponent
    {
        std::size_t damage;
        float speed;
        Utils::Vector2 position;
        Utils::Vector2 direction;
        Enums::TeamGroup team = Enums::TeamGroup::ENEMY;
    };

} // namespace ECS::Components
