/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** walkingAI
*/

#pragma once

#include "ECS/Containers/Registry.hpp"
#include "ECS/Containers/SparseArray.hpp"
#include "ECS/Components/WalkingAIComponent.hpp"
#include "ECS/Components/TargetComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Components/CollisionComponent.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/HitBoxComponent.hpp"

namespace ECS::Systems {
    /**
     * @brief Component owned by entities that move toward a target by walking
     */
    void walkingAI(
        Containers::Registry &,
        Containers::SparseArray<Components::WalkingAIComponent> &,
        Containers::SparseArray<Components::TargetComponent> &,
        Containers::SparseArray<Components::VelocityComponent> &,
        Containers::SparseArray<Components::CollisionComponent> &,
        Containers::SparseArray<Components::PositionComponent> &,
        Containers::SparseArray<Components::HitBoxComponent> &);
} // namespace ECS::Systems
