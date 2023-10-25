/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** findTarget
*/

#pragma once

#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/TargetComponent.hpp"
#include "ECS/Components/HPComponent.hpp"
#include "ECS/Components/InvincibleTimerComponent.hpp"
#include "ECS/Components/TeamComponent.hpp"

namespace ECS::Systems {
    /**
     * @brief Finds a new target for entities that target the NullEntity.
     * The new target is the first entity that is not in the same team as the
     * entity and can be hurt.
     */
    void findTarget(
        Containers::Registry &registry,
        ECS::Containers::SparseArray<ECS::Components::TargetComponent> &targets,
        ECS::Containers::SparseArray<ECS::Components::HPComponent> &hpComponents,
        ECS::Containers::SparseArray<ECS::Components::InvincibleTimerComponent> &invincibleTimers,
        ECS::Containers::SparseArray<ECS::Components::TeamComponent> &teams);
} // namespace ECS::Systems
