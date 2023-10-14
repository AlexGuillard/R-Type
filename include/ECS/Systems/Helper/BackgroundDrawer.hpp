/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** BackgroundDrawer.hpp
*/

#pragma once

#include <cstddef>

#include <raylib.h>

namespace ECS::Systems::Helper {

    class BackgroundDrawer {
    public:
        /**
         * @brief Construct a new Sprite Sheet Drawer object
         * @param texture Texture to draw
         * @param frameRatio Ratio of the frame in the texture$
         */
        BackgroundDrawer(Texture2D texture, float frameScale);

        /**
         * @brief Draws the given frame at the given position
         * @param x Position of where to draw the frame (ie 100 for the 100th pixel)
         * @param y Position of where to draw the frame (ie 100 for the 100th pixel)
         * @note This function is not recommended for animations, use the other overload instead
         */
        void draw(int posX, int posY);
        /**
         * @brief Draws the current frame at the given position
         * @param position Position on the screen where to draw the frame
         */
        void draw(const Vector2 &position);
        /**
         * @brief Go to the next frame
         * @return The new frame
         */
    private:
        Texture2D m_texture;
        float m_frameScale = 1.0;
        Vector2 m_frameSize;
    };

}; // namespace ECS::Systems::Helper
