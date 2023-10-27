/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** utils
*/

#include "Player/utils.hpp"
#include "constants.hpp"

namespace Player {
    template <typename T>
    static T clamp(T value, T min, T max)
    {
        if (value < min) {
            return min;
        }
        if (value > max) {
            return max;
        }
        return value;
    }

    template <typename T>
    static T abs(T value)
    {
        return value < 0 ? -value : value;
    }

    void updateVelocity(
        float &velX,
        float &velY,
        std::size_t up,
        std::size_t down,
        std::size_t left,
        std::size_t right)
    {
        if (up > 0) {
            velY -= up * Constants::playerSpeed;
        } else if (down > 0) {
            velY += down * Constants::playerSpeed;
        } else {
            velY = 0;
        }
        if (left > 0) {
            velX -= left * Constants::playerSpeed;
        } else if (right > 0) {
            velX += right * Constants::playerSpeed;
        } else {
            velX = 0;
        }
        velX = clamp(velX, -(float)Constants::playerSpeed, (float)Constants::playerSpeed);
        velY = clamp(velY, -(float)Constants::playerSpeed, (float)Constants::playerSpeed);
    }
} // namespace Player
