/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** utils
*/

#pragma once // NOLINT

namespace Player {
    /**
     * @brief Function that moves a player.
     * Uses the speed constant to move the player.
     * @param velX X velocity of the player
     * @param velY Y velocity of the player
     * @param up If the player is going up
     * @param down If the player is going down
     * @param left If the player is going left
     * @param right If the player is going right
     */
    void movePlayer(
        float &velX,
        float &velY,
        bool up,
        bool down,
        bool left,
        bool right);
} // namespace Player
