/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** CollidableComponent
*/

#pragma once

namespace ECS::Components {

    /**
     * @brief Component that indicates that an entity can collide with other entities.
     * For this component to be useful, the entity must also have a hitbox and
     * a position component.
     */
    struct CollidableComponent {};


} // namespace ECS::Components
