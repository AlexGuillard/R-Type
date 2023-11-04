/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** MissileSpawnPointComponent
*/

#pragma once

#include <vector>
#include <tuple>

#include "enums.hpp"
#include "Utils.hpp"

namespace ECS::Components {
    /**
     * @brief Components that defines the spawn points of missiles.
     * If it is missing, 1 spawn point at the top left of the entity is used.
     *
     * @param spawnPoints Vector of:
     * - The position of the spawn point relative to the entity. (range [0, 1])
     * - The type of the missile to spawn.
     * - The cooldown between each shot. (in seconds)
     * - The timer for the cooldown. (in seconds)
     */
    struct MissileSpawnPointComponent
    {
        std::vector<
            std::tuple<
            Utils::Vector2,
            Enums::ShotType,
            float,
            float
            >
        > spawnPoints;
        std::size_t currentSpawnPoint = 0;
    };

} // namespace ECS::Components
