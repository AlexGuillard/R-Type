/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** collision
*/

#pragma once

#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Components/HitBoxComponent.hpp"
#include "ECS/Components/CollisionComponent.hpp"
#include "ECS/Components/CollidableComponent.hpp"

namespace ECS::Systems {

    /**
     * @brief Detects collisions between entities with collidable components and
     * update their collision components accordingly.
     * @details The collision component of an entity contains the list of entities
     * that are colliding with it. If an entity has no collision component, it means
     * that it is not colliding with any other entity.
     *
     * @param registry The ECS registry containing all entities and their components.
     * @param positions Position components for all entities.
     * @param hitboxes Hitbox components for all entities.
     * @param collidables Collidable components for all entities.
     * @param collisions Collision components for all entities.
     */
    void collision(
        Containers::Registry &registry,
        Containers::SparseArray<Components::PositionComponent> &positions,
        Containers::SparseArray<Components::VelocityComponent> &velocities,
        Containers::SparseArray<Components::HitBoxComponent> &hitboxes,
        Containers::SparseArray<Components::CollidableComponent> &collidables,
        Containers::SparseArray<Components::CollisionComponent> &collisions);

} // namespace ECS::Systems
