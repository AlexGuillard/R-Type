/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** constants
*/

#pragma once

#include <cstddef>
#include <cstdint>

namespace Constants {
    // Player
    const std::size_t playerSpeed = 500;
    const std::size_t playerNbFrameToMaxSpeed = 5;
    const std::size_t playerNbFrameToStop = 5;

    // Missile
    const std::size_t bydoMissileSpeed = 50; // pixels per second

    // Camera
    const std::size_t cameraDefaultWidth = 960;
    const std::size_t cameraDefaultHeight = 540;

    // Game
    const std::size_t frameRate = 120;
    static constexpr std::size_t defaultScrollSpeed = 0;
    // time (in s) player need to hold the fire button to shoot a wave beam
    const double timeNeededForWaveBeam = 1.;
    const uint8_t maxWaveBeamStrength = 5;
    const float waveBeamSpeed = 500; // pixels per second
    const std::size_t waveBeamBaseDamage = 2;

    // Server
    // in milliseconds
    const std::size_t tickUpdate = 1000 / 60;

} // namespace Constants
