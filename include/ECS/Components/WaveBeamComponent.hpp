/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** WaveBeamComponent
*/

#pragma once

#include <cstddef>
#include <sys/types.h>

namespace ECS::Components {
    const uint8_t maxWaveBeamStrength = 5;
    const float waveBeamSpeed = 500;
    const std::size_t waveBeamBaseDamage = 2;
    /**
     * @brief Component for entities that request to spawn a wave beam
     * @param x Position on the x axis
     * @param y Position on the y axis
     */
    struct WaveBeamComponent {
        float x;
        float y;
        std::size_t damage = waveBeamBaseDamage;
        uint8_t strength = 1;
    };
}; // namespace ECS::Components
