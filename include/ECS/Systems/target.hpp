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
    void target(
        Containers::Registry &registry,
        Containers::SparseArray<Components::TargetComponent> &targets,
        Containers::SparseArray<Components::PositionComponent> &positions);
} // namespace ECS::Systems
