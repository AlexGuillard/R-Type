/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** bydoShootingAI
*/

#pragma once

#include "ECS/Containers/Registry.hpp"
#include "ECS/Containers/SparseArray.hpp"
#include "ECS/Components/BydoShootingAIComponent.hpp"
#include "ECS/Components/TargetComponent.hpp"
#include "ECS/Components/InRangeComponent.hpp"
#include "ECS/Components/TeamComponent.hpp"
#include "ECS/Components/PositionComponent.hpp"

namespace ECS::Systems {
    /**
     * @brief System that makes entities with a bydoShootingAIComponent shoot
     * if possible
     *
     * @param registry Registry containing all entities
     * @param AIs Array of bydoShootingAIComponents
     * @param targets Array of targetComponents
     * @param inRange Array of inRangeComponents
     * @param teams Array of teamComponents
     */
    void bydoShootingAI(
        Containers::Registry &registry,
        Containers::SparseArray<Components::BydoShootingAIComponent> &AIs,
        Containers::SparseArray<Components::TargetComponent> &targets,
        Containers::SparseArray<Components::InRangeComponent> &inRange,
        Containers::SparseArray<Components::TeamComponent> &teams,
        Containers::SparseArray<Components::PositionComponent> &positions
    );
} // namespace ECS::Systems
