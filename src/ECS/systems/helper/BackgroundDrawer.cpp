/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** BackgroundDrawer.cpp
*/

#include <utility>

#include <raylib.h>

#include "ECS/Systems/Helper/BackgroundDrawer.hpp"

namespace ECS::Systems::Helper {

    BackgroundDrawer::BackgroundDrawer(Texture2D texture, float frameScale): m_texture(texture), m_frameScale(frameScale)
    {
        this->m_frameSize = {
            (float)texture.width * frameScale,
            (float)texture.height * frameScale
        };
    }

    void BackgroundDrawer::draw(int posX, int posY)
    {
        DrawTexture(m_texture, posX, posY, WHITE);
    }

    void BackgroundDrawer::draw(const Vector2 &position)
    {

        this->draw(position.x, position.y);
    }
}; // namespace ECS::Systems::Helper
