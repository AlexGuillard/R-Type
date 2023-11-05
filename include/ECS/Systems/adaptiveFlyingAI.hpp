/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** FlyingAI
*/

#pragma once

#include "ECS/Containers/Registry.hpp"
#include "ECS/Containers/SparseArray.hpp"
#include "ECS/Components/AdaptiveFlyingAIComponent.hpp"
#include "ECS/Components/FlyingAIComponent.hpp"
#include "ECS/Components/TargetComponent.hpp"

namespace ECS::Systems {
    /**
     * @brief Moves the entity towards its target faster if it is far away
     *
     * @param registry
     * @param AIs
     * @param targets
     * @param positions
     * @param velocities
     */
    void adaptiveFlyingAI(
        Containers::Registry &registry,
        Containers::SparseArray<Components::AdaptiveFlyingAIComponent> &AIs,
        Containers::SparseArray<Components::FlyingAIComponent> &flyingAIs,
        Containers::SparseArray<Components::TargetComponent> &targets);
} // namespace ECS::Systems
