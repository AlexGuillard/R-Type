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
#include "ECS/Components/TeamComponent.hpp"

namespace ECS::Systems {
    /**
     * @brief Makes every solid entity unpenetrable by other entities
    */
    void solid(
        Containers::Registry &,
        Containers::SparseArray<Components::SolidComponent> &,
        Containers::SparseArray<Components::HitBoxComponent> &,
        Containers::SparseArray<Components::CollisionComponent> &,
        Containers::SparseArray<Components::PositionComponent> &,
        Containers::SparseArray<Components::VelocityComponent> &,
        Containers::SparseArray<Components::TeamComponent> &);
} // namespace ECS::Systems
