/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** background.hpp
*/

#pragma once

#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/LevelComponent.hpp"
#include "ECS/Components/BackgroundComponent.hpp"

namespace ECS::Systems {
    /**
     * @brief Draws the background with a level and a background component
     */
    void background(
        Containers::Registry &registry,
        Containers::SparseArray<Components::PositionComponent> &positions,
        Containers::SparseArray<Components::LevelComponent> &levels,
        Containers::SparseArray<Components::BackgroundComponent> &backgrounds);

}; // namespace ECS::Systems
