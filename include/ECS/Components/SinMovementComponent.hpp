/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** SinMovementComponent
*/

#pragma once

#include "constants.hpp"

namespace ECS::Components {
    const int defaultSinXSpeed = Constants::cameraDefaultWidth / 10 * -1; // takes 10 seconds to go right to left
    const int defaultSinAmplitude = Constants::cameraDefaultHeight / 10;
    const float defaultSinFrequency = 0.01;
    /**
     * @brief Component that makes the entity move in a sine wave.
     * Every value is in pixels per second.
     * The equation is: y = amplitude * sin(frequency * (t + horizontalOffset)) + verticalOffset.
     * @param verticalOffset The vertical offset of the sine wave. (start position of the entity on the y axis) (def: 0.0F)
     * @param horizontalOffset The horizontal offset of the sine wave. (start position of the entity on the x axis) (def: 0.0F)
     * @param speed The speed at which the entity moves on the x axis. (def: defaultSinXSpeed = -100)
     * @param amplitude The amplitude of the sine wave. (def: defaultSinAmplitude = 100)
     * @param frequency The frequency of the sine wave. (def: defaultSinFrequency = 100)
     * @param t Where in the sine wave the entity is. (def: 0.0F)
     */
    struct SinMovementComponent {
        int verticalOffset = 0;
        int horizontalOffset = 0;
        float speed = defaultSinXSpeed;
        float amplitude = defaultSinAmplitude;
        float frequency = defaultSinFrequency;
        float t = 0.0F;
    };
}; // namespace ECS::Components
