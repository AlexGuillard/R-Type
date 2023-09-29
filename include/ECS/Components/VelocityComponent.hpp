/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** VelocityComponent
*/

#pragma once

namespace ECS::Components {
    /**
     * @brief Component that contains the velocity of an entity
     * @param x Velocity on the x axis
     * @param y Velocity on the y axis
     */
    struct VelocityComponent {
        float x;
        float y;
    };
}; // namespace ECS::Components
