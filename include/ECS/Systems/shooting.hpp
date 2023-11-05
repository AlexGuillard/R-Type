/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** controller
*/

#pragma once

#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/ShootingTimerComponent.hpp"
#include "ECS/Components/PositionComponent.hpp"

namespace ECS::Systems {
    /**
     * @brief Handles the input of the player
     */
    void shooting(
        Containers::Registry &registry,
        Containers::SparseArray<Components::ShootingTimerComponent> &shootingTimers,
        Containers::SparseArray<Components::PositionComponent> &positions);
}; // namespace ECS::Systems
