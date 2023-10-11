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
     */
    struct BydoShootingAIComponent {
        float shootCooldown = 0.0F;
        float shootCooldownMax = 0.0F;
    };

} // namespace ECS::Components
