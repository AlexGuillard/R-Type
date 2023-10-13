/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** gravity
*/

#pragma once

#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/GravityComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"

namespace ECS::Systems {
    /**
     * @brief Add gravity to velocity
     */
    void gravity(
        Containers::Registry &registry,
        ECS::Containers::SparseArray<ECS::Components::VelocityComponent> &velocities,
        Containers::SparseArray<Components::GravityComponent> &gravity);
};
