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
    const float playerSpeed = 500;

    // Camera
    const std::size_t cameraDefaultWidth = 960;
    const std::size_t cameraDefaultHeight = 540;

    // Game
    const std::size_t frameRate = 120;
    const int deathZone = 75; // how far from the edge of the screen an entity can go before being killed
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
