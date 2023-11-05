/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ShootingTimerComponent
*/

#pragma once

#include "enums.hpp"

namespace ECS::Components {
    /**
     * @brief Component for entities that shoot at regular intervals
     * @param shootCooldown The time between two shots (in seconds).
     * @param shotType The type of shot to shoot.
     * @param _shootCooldownTimer The time left before the next shot (in
     */
    struct ShootingTimerComponent
    {
        float shootCooldown;
        Enums::ShotType shotType;
        float _shootCooldownTimer = .0F;
    };

} // namespace ECS::Components
