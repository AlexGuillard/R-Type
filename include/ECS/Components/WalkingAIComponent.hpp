/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** WalkingAIComponent
*/

#pragma once

#include <utility>

namespace ECS::Components {
    /**
     * @brief Component owned by entities that have a target and need to move
     * towards it. Note that the entity needs to be grounded to move.
     * @param preferredDistance Pair of floats representing the preferred
     * distance between the entity and its target (first: min, second: max)
     * @param speed Walking speed of the entity
     * @param dropsDownLedge Whether the entity can drops down ledges
     * (default: false)
     * @param jumpsOverObstacle Whether the entity can jump over obstacles
     * (default: false)
     */
    struct WalkingAIComponent {
        std::pair<float, float> preferredDistance; // first: min, second: max
        float speed;
        bool dropsDownLedge = false;
        bool jumpsOverObstacle = false;
    };
} // namespace ECS::Components
