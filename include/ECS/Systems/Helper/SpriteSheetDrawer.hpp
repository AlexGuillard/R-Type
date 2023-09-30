/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** SpriteSheetDrawer
*/

#pragma once

#include <cstddef>

#include <raylib.h>

namespace ECS::Systems::Helper {

    class SpriteSheetDrawer {
    public:
        /**
         * @brief Construct a new Sprite Sheet Drawer object
         * @param texture Texture to draw
         * @param frameRatio Ratio of the frame in the texture
         * ex: { 16, 1 } for a sprite sheet with 16 columns and 1 row
         * @param start First frame of the animation
         * ex: { 3, 0 } for the 4th frame of the first row
         * @param end Last frame of the animation
         * ex: { 8, 0 } for the 9th frame of the first row
         * @param boomerang If true, the animation will go back and forth
         * @param frame Frame to start the animation at
         * @param forward If true, the animation will go forward
         */
        SpriteSheetDrawer(Texture2D texture, Vector2 frameRatio,
            Vector2 start, Vector2 end, bool boomerang, std::size_t frame = 0, bool forward = true);

        bool isForward() const;

        /**
         * @brief Set the start and end frame of the animation
         * @param start start frame position
         * ie { 2, 5 } for the 3rd frame of the 6th row
         * @param end end frame position
         * ie { 4, 5 } for the 5th frame of the 6th row
         */
        void setRange(Vector2 start, Vector2 end);
        /**
         * @brief Draws the given frame at the given position
         * @param row Row of the frame (ie 5 for the 6th row)
         * @param column Column of the frame (ie 2 for the 3rd column)
         * @param x Position of where to draw the frame (ie 100 for the 100th pixel)
         * @param y Position of where to draw the frame (ie 100 for the 100th pixel)
         * @note This function is not recommended for animations, use the other overload instead
         */
        void draw(int row, int column, int posX, int posY);
        /**
         * @brief Draws the current frame at the given position
         * @param position Position on the screen where to draw the frame
         */
        void draw(const Vector2 &position);
        /**
         * @brief Go to the next frame
         * @return The new frame
         */
        int next();
        /**
         * @brief Draw the next frame at the given position
         * @param position Position on the screen where to draw the frame
         * @see next()
         * @see draw()
         * @return The new frame
         */
        int drawNext(const Vector2 &position);
        /**
         * @brief Reset the animation to the first frame
         */
        void reset();
    private:
        Texture2D m_texture;
        std::size_t m_rows;
        std::size_t m_columns;
        std::size_t m_start;
        std::size_t m_end;
        bool m_boomerang;
        std::size_t m_currentFrame;
        std::size_t m_nbFrames;
        Vector2 m_frameSize;
        bool m_forward;
    };

}; // namespace ECS::Systems::Helper
