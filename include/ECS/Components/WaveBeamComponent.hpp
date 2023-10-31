/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** WaveBeamComponent
*/

#pragma once

#include <cstddef>
#include <sys/types.h>
#include <cstdint>

#include "ECS/Components/TeamComponent.hpp"
#include "constants.hpp"

namespace ECS::Components {
    /**
     * @brief Component for entities that request to spawn a wave beam
     * @param x Position on the x axis
     * @param y Position on the y axis
     */
    struct WaveBeamComponent {
        float x;
        float y;
        TeamComponent team;
        std::size_t damage = Constants::waveBeamBaseDamage;
        uint8_t strength = 1;
    };
}; // namespace ECS::Components
