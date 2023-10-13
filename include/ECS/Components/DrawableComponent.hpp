/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** DrawableComponent
*/

#pragma once

#include <cstddef>

#include <raylib.h>

#include "Assets/generatedAssets.hpp"

namespace ECS::Components {
    // size of the texture path
    const std::size_t maxTexturePathSize = 256;
    /**
     * @brief Component that contains the data needed to draw a sprite
     * @param spriteSheetIndex The index of the sprite sheet to use
     * @param frameRatio Ratio of the frame in the texture
     * ex: { 16, 1 } for a sprite sheet with 16 columns and 1 row
     * @param start First frame of the animation
     * ex: { 3, 0 } for the 4th frame of the first row
     * @param end Last frame of the animation
     * ex: { 8, 0 } for the 9th frame of the first row
     * @param boomerang If true, the animation will go back and forth
     * @param fps Number of frames per second
     * @param frame Current frame
     * @param timeSinceLastFrame Time since the last frame in seconds (used internally)
     * @param forward If true, the animation will go forward
     * @see SpriteSheetDrawer
     */
    struct DrawableComponent {
        Assets::AssetsIndex spriteSheetIndex;
        Vector2 frameRatio = { 1, 1 };
        Vector2 start = { 0, 0 };
        Vector2 end = { 0, 0 };
        bool boomerang = false;
        std::size_t fps = 1;
        std::size_t frame = 0;
        float timeAtLastFrameChange = 0.0F;
        bool forward = true;
    };
} // namespace ECS::Components
