/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AdaptiveFlyingAIComponent
*/

#pragma once

#include <utility>
#include <array>

namespace ECS::Components {
    /**
     * @brief Component that changes FlyingAIComponent depending on the distance
     * @param speedPerDistance 3 speed of the entity per distance.
     * (maxDistance, speed) where maxDistance is the distance at which the
     *
    */
    struct AdaptiveFlyingAIComponent
    {
        std::array<std::pair<float, float>, 3> speedPerDistance;
    };
} // namespace ECS::Components
