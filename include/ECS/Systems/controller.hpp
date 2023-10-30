/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** controller
*/

#pragma once

#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Components/TeamComponent.hpp"
#include "ECS/Components/ControllableComponent.hpp"

namespace ECS::Systems {
    /**
     * @brief Handles the input of the player
     */
    void controller(
        Containers::Registry &registry,
        ECS::Containers::SparseArray<ECS::Components::PositionComponent> &positions,
        Containers::SparseArray<Components::VelocityComponent> &velocities,
        ECS::Containers::SparseArray<Components::TeamComponent> &teams,
        Containers::SparseArray<Components::ControllableComponent> &controllables);
}; // namespace ECS::Systems
