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

#include "enums.hpp"
#include "ECS/Components/TeamComponent.hpp"
#include "constants.hpp"

namespace ECS::Components {
    /**
     * @brief Component for entities that request to spawn a wave beam
     * @param x Position on the x axis
     * @param y Position on the y axis
     * @param team Team of the entity that requested the wave beam (default: Enums::TeamGroup::ALLY)
     * @param damage Damage of the wave beam (default: Constants::waveBeamBaseDamage)
     * @param strength Strength of the wave beam (default: 1)
     */
    struct WaveBeamComponent {
        float x;
        float y;
        Enums::TeamGroup team = Enums::TeamGroup::ALLY;
        std::size_t damage = Constants::waveBeamBaseDamage;
        uint8_t strength = 1;
    };
}; // namespace ECS::Components
