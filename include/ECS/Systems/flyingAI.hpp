/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** FlyingAI
*/

#pragma once

#include "ECS/Containers/Registry.hpp"
#include "ECS/Containers/SparseArray.hpp"
#include "ECS/Components/FlyingAIComponent.hpp"
#include "ECS/Components/TargetComponent.hpp"
#include "ECS/Components/TeamComponent.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"

namespace ECS::Systems {
    void flyingAI(
        Containers::Registry &registry,
        Containers::SparseArray<Components::FlyingAIComponent> &AIs,
        Containers::SparseArray<Components::TargetComponent> &targets,
        Containers::SparseArray<Components::PositionComponent> &positions,
        Containers::SparseArray<Components::VelocityComponent> &velocities);
} // namespace ECS::Systems
