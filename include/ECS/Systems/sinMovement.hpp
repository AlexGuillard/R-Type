/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** sinMovement
*/

#pragma once

#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/SinMovementComponent.hpp"
#include "ECS/Components/PositionComponent.hpp"

namespace ECS::Systems {
    /**
     * @brief Component owned by entities that move in a sine wave
     */
    void sinMovement(
        Containers::Registry &registry,
        Containers::SparseArray<Components::SinMovementComponent> &sinMovements,
        Containers::SparseArray<Components::PositionComponent> &positions);
} // namespace ECS::Systems
