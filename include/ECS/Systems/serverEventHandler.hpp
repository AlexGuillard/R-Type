/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** serverEventHandler
*/

#pragma once // NOLINT

#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Components/TeamComponent.hpp"

namespace ECS::Systems {
    /**
     * @brief Handles the input of the players and moves them
     *
     * @param registry The registry of the engine
     * @param missileRequests
     * @param waveBeamRequests
     */
    void serverEventHandler(
        Containers::Registry &registry,
        Containers::SparseArray<Components::PositionComponent> &positions,
        Containers::SparseArray<Components::VelocityComponent> &velocities,
        Containers::SparseArray<Components::TeamComponent> &teams);
} // namespace ECS::Systems
