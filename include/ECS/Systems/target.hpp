/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** target
*/

#pragma once

#include "ECS/Containers/Registry.hpp"
#include "ECS/Containers/SparseArray.hpp"
#include "ECS/Components/TargetComponent.hpp"
#include "ECS/Components/PositionComponent.hpp"

namespace ECS::Systems {
    void updateTarget(
        Containers::Registry &registry,
        std::size_t eId,
        Components::TargetComponent &target,
        Components::PositionComponent &position,
        ECS::Containers::SparseArray<Components::PositionComponent> &positions);

    void target(
        Containers::Registry &registry,
        Containers::SparseArray<Components::TargetComponent> &targets,
        Containers::SparseArray<Components::PositionComponent> &positions);
} // namespace ECS::Systems
