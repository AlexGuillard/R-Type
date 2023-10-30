/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** controller
*/

#pragma once

#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/MissileComponent.hpp"
#include "ECS/Components/WaveBeamComponent.hpp"
#include "ECS/Components/BydoShotComponent.hpp"

namespace ECS::Systems {
    /**
     * @brief Handles the input of the player
     */
    void shooting(
        Containers::Registry &registry,
        Containers::SparseArray<Components::MissileComponent> &missileRequests,
        Containers::SparseArray<Components::WaveBeamComponent> &waveBeamRequests,
        Containers::SparseArray<Components::BydoShotComponent> &bydoShotRequests);
}; // namespace ECS::Systems
