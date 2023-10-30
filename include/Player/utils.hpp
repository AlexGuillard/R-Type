/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** utils
*/

#pragma once // NOLINT

#include <cstddef>

namespace Player {
    /**
     * @brief Function that moves a player.
     * Uses the speed constant to move the player.
     * @param velX X velocity of the player
     * @param velY Y velocity of the player
     * @param up Nb of time the player pressed up
     * @param down Nb of time the player pressed down
     * @param left Nb of time the player pressed left
     * @param right Nb of time the player pressed right
     */
    void updateVelocity(
        float &velX,
        float &velY,
        std::size_t up,
        std::size_t down,
        std::size_t left,
        std::size_t right);

    /**
     * @brief Calculate Wave beam strength based on the time the button was held
     */
    int calculateWaveBeamStrength(double timeButtonHeld);
} // namespace Player
