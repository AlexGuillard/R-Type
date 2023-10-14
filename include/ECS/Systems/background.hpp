/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** background.hpp
*/

#pragma once

namespace ECS::Systems {
    /**
     * @brief Draws the entities with a position and a drawable component
     */
    void background(
        Containers::Registry &registry,
        Containers::SparseArray<Components::BackgroundComponent> &backgrounds);

}; // namespace ECS::Systems
