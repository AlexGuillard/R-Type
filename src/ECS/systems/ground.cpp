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
                int limitScreen = -static_cast<int>(Constants::cameraDefaultWidth * 2);
                if ((time - ground->timeAtLastFrameChange) > ground->fps) {
                    ground->timeAtLastFrameChange = time;
                     position->x -= ground->paralaxSpeed;
                        if(position->x <= limitScreen) {
                            position->x = 0;
                        }
                }
                Rectangle sourceRec = { 0, 0, float(texture.width), float(texture.height) };
                Rectangle destRecOne = { position->x, position->y,
                Constants::cameraDefaultWidth * 2,
                Constants::cameraDefaultHeight * 0.1};
                 Rectangle destRecTwo = {
                    Constants::cameraDefaultWidth * 2 + position->x,
                    position->y,
                    Constants::cameraDefaultWidth * 2,
                    Constants::cameraDefaultHeight * 0.1
                 };
                DrawTexturePro(texture, sourceRec, destRecOne, {0, 0}, 0.0f, WHITE);
                DrawTexturePro(texture, sourceRec, destRecTwo, {0, 0}, 0.0f, WHITE);

            }
        }
        Screen::Display::endDrawCamera();
    }

}; // namespace ECS::Systems
