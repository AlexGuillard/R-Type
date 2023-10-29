/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ground.cpp
*/

#include <unordered_map>

#include "ECS/Components/GroundComponent.hpp"
#include "ECS/Components/LevelComponent.hpp"
#include "ECS/Containers/Registry.hpp"
#include "ECS/Containers/zipper/IndexedZipper.hpp"
#include "ECS/Systems/ground.hpp"
#include "Assets/AssetLoader.hpp"
#include "client/display/Display.hpp"


namespace ECS::Systems {

    void ground(
        [[maybe_unused]] Containers::Registry &registry,
        Containers::SparseArray<Components::PositionComponent> &positions,
        Containers::SparseArray<Components::LevelComponent> &levels,
        Containers::SparseArray<Components::GroundComponent> &grounds
    )
    {
        Screen::Display::beginDrawCamera();
        for (auto &&[eId, position, level, ground] : Containers::IndexedZipper(positions, levels, grounds)) {
            if (eId == (level->level - 1)) {
                  const double time = GetTime();
                auto &&texture = Assets::AssetLoader::loadTexturePng(ground->texture);
                if ((time - ground->timeAtLastFrameChange) > ground->fps) {
                    ground->timeAtLastFrameChange = time;
                     position->x -= ground->paralaxSpeed;
                        if(position->x <= (-(texture.width) * ground->frameScale)) {
                            position->x = 0;
                        }
                }

                DrawTextureEx(texture,
                Vector2(position->x, position->y),
                double(0.0), ground->frameScale, WHITE);
                DrawTextureEx(texture,
                Vector2(texture.width * ground->frameScale + position->x, position->y),
                double(0.0), ground->frameScale, WHITE);
            }
        }
        Screen::Display::endDrawCamera();
    }

}; // namespace ECS::Systems
