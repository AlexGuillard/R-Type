/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** CollisionComponent
*/

#pragma once

#include <set>
#include "ECS/Entity.hpp"

namespace ECS::Components {

    /**
     * @brief Component that contains the list of entities that are colliding with
     * the entity.
     * @details If an entity has no collision component, it means that it is not
     * colliding with any other entity.
     */
    struct CollisionComponent {
        std::set<Entity> collisions;
    };


} // namespace ECS::Components
