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

    struct CollisionComponent {
        std::set<Entity> collisions;
    };


} // namespace ECS::Components
