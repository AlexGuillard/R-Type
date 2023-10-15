/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** BackgroundComponent.hpp
*/

#pragma once

#include <cstddef>

#include <raylib.h>

#include "Assets/generatedAssets.hpp"

namespace ECS::Components {
    /**
     * @brief Component that contains the data needed for a parallax background
     * @param texturePath Path to the background texture
     * @param frameScale The scale of the background
     * @see SpriteSheetDrawer
     */
    struct BackgroundComponent {
        Texture2D texture;
        double frameScale = 1.0;
        double paralaxSpeed = 1.0;
    };
} // namespace ECS::Components
