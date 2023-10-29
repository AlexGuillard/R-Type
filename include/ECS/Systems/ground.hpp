/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ground.hpp
*/

#pragma once

#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/LevelComponent.hpp"
#include "ECS/Components/GroundComponent.hpp"

namespace ECS::Systems {
    /**
     * @brief Draws the background with a level and a background component
     */
    void ground(
        Containers::Registry &registry,
        Containers::SparseArray<Components::PositionComponent> &positions,
        Containers::SparseArray<Components::LevelComponent> &levels,
        Containers::SparseArray<Components::GroundComponent> &grounds);

}; // namespace ECS::Systems
