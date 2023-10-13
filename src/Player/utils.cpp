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

    void movePlayer(
        float &velX,
        float &velY,
        bool up,
        bool down,
        bool left,
        bool right)
    {
        const float acceleration = Constants::playerMaxSpeed / (float)Constants::playerNbFrameToMaxSpeed;
        const float deceleration = Constants::playerMaxSpeed / (float)Constants::playerNbFrameToStop;
        if (up) {
            velY -= 1 * acceleration;
        } else if (down) {
            velY += 1 * acceleration;
        } else {
            if (abs(velY) < deceleration) {
                velY = 0;
            } else {
                velY += (velY > 0 ? -1 : 1) * deceleration;
            }
        }
        if (left) {
            velX -= 1 * acceleration;
        } else if (right) {
            velX += 1 * acceleration;
        } else {
            if (abs(velX) < deceleration) {
                velX = 0;
            } else {
                velX += (velX > 0 ? -1 : 1) * deceleration;
            }
        }
        velX = clamp(velX, -(float)Constants::playerMaxSpeed, (float)Constants::playerMaxSpeed);
        velY = clamp(velY, -(float)Constants::playerMaxSpeed, (float)Constants::playerMaxSpeed);
    }
} // namespace Player
