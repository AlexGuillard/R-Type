/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** HorizontalScrollComponent
*/

#pragma once // NOLINT

namespace ECS::Components {
    /**
     * @brief Component for entities affected by level horizontal scroll.
     * @param speed Horizontal scroll speed in pixels per second.
     */
    struct HorizontalScrollComponent {
        float speed;
    };
} // namespace ECS::Components
