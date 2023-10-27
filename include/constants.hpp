/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** constants
*/

#pragma once

#include <cstddef>

namespace Constants {
    // Player
    const std::size_t playerMaxSpeed = 500;
    const std::size_t playerNbFrameToMaxSpeed = 5;
    const std::size_t playerNbFrameToStop = 5;

    // Missile
    const std::size_t bydoMissileSpeed = 50; // pixels per second

    // Camera
    const std::size_t cameraDefaultWidth = 960;
    const std::size_t cameraDefaultHeight = 540;

    // Game
    static constexpr std::size_t defaultScrollSpeed = 0;

} // namespace Constants
