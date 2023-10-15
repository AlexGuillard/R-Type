/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** background.hpp
*/

#pragma once

namespace ECS::Systems {
    /**
     * @brief Draws the background with a level and a background component
     */
    void background(
        Containers::Registry &registry,
        Containers::SparseArray<Components::LevelComponent> &levels,
        Containers::SparseArray<Components::BackgroundComponent> &backgrounds);

}; // namespace ECS::Systems
