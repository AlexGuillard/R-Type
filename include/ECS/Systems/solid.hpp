/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** solid
*/

#pragma once

#include "ECS/Containers/Registry.hpp"
#include "ECS/Containers/SparseArray.hpp"
#include "ECS/Components/SolidComponent.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/HitBoxComponent.hpp"
#include "ECS/Components/CollisionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"

namespace ECS::Systems {
    void solid(
        Containers::Registry &,
        Containers::SparseArray<Components::SolidComponent> &,
        Containers::SparseArray<Components::HitBoxComponent> &,
        Containers::SparseArray<Components::CollisionComponent> &,
        Containers::SparseArray<Components::PositionComponent> &,
        Containers::SparseArray<Components::VelocityComponent> &);
} // namespace ECS::Systems
