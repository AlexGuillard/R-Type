/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** pickup
*/

#pragma once

#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/PickupComponent.hpp"
#include "ECS/Components/CollisionComponent.hpp"

namespace ECS::Systems {
    /**
     * @brief System that handles the pickup of entities
     *
     * @param registry registry of the ECS
     * @param pickups pickups of the ECS
     */
    void pickup(
        Containers::Registry &registry,
        Containers::SparseArray<Components::PickupComponent> &pickups,
        Containers::SparseArray<Components::CollisionComponent> &collisions);
} // namespace ECS::Systems
