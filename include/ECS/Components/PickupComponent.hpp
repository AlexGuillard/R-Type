/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PickupComponent
*/

#pragma once

#include "enums.hpp"

namespace ECS::Components {
    /**
     * @brief Component for entities that can be picked up
     *
     */
    struct PickupComponent {
        Enums::PickupType type;
        union {
            struct {
                float shootCooldown;
                Enums::ShotType shotType;
            } shootingTimer;
        } data;
    };

} // namespace ECS::Components
