/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** BydoShootingAIComponent
*/

#pragma once

namespace ECS::Components {
    /**
     * @brief Component for the BydoShootingAI system.
     * Defines the ability to shoot for a Bydo entity and the cooldown between
     * each shot.
     * Entity must have a TargetComponent, a PositionComponent, an
     * InRangeComponent and (optionally), a TeamComponent (defaults to Enemy).
     * @param shootCooldown time between each shot in seconds
     * @param shotSpeed speed of the shot in pixels per second
     * @param _shootCooldownTimer internal timer for the cooldown
     */
    struct BydoShootingAIComponent {
        float shootCooldown = 0.0F;
        float shotSpeed = 10.0F;
        double _shootCooldownTimer = 0.;
    };

} // namespace ECS::Components
