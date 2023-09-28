/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** HitBoxComponent
*/

#pragma once

#include <cstddef>

namespace ECS::Components {
    /**
     * @brief Component for entities that have a hitbox
     * @param width Width of the hitbox
     * @param height Height of the hitbox
     */
    struct HitBoxComponent {
        std::size_t width;
        std::size_t height;
    };
}; // namespace ECS::Components
