/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** background.cpp
*/

#include <unordered_map>

#include "ECS/Components/BackgroundComponent.hpp"
#include "ECS/Components/LevelComponent.hpp"
#include "ECS/Containers/Registry.hpp"
#include "ECS/Containers/zipper/IndexedZipper.hpp"
#include "ECS/Systems/background.hpp"
#include "Assets/AssetLoader.hpp"
#include "client/display/Display.hpp"


namespace ECS::Systems {

    void background(
        [[maybe_unused]] Containers::Registry &registry,
        Containers::SparseArray<Components::PositionComponent> &positions,
        Containers::SparseArray<Components::LevelComponent> &levels,
        Containers::SparseArray<Components::BackgroundComponent> &backgrounds
    )
    {
        Screen::Display::beginDrawCamera();
        for (auto &&[eId, position, level, background] : Containers::IndexedZipper(positions, levels, backgrounds)) {
            if (eId == (level->level - 1)) {
                position->x -= background->paralaxSpeed;
                if(position->x <= (-(background->texture.width) * background->frameScale)) {
                    position->x = 0;
                }
                DrawTextureEx(background->texture,
                (Vector2) {position->x, 0},
                (float) 0.0, background->frameScale, WHITE);
                DrawTextureEx(background->texture,
                (Vector2) {background->texture.width * background->frameScale + position->x, 0},
                (float) 0.0, background->frameScale, WHITE);
            }
        }
        Screen::Display::endDrawCamera();
    }

}; // namespace ECS::Systems
