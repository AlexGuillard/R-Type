/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** gravity
*/

#pragma once

#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/GravityComponent.hpp"

namespace ECS::Systems {
    /**
     * @brief Add gravity to velocity
     */
    void gravity(
        Containers::Registry &registry,
        Containers::SparseArray<Components::GravityComponent> &gravity);
};
