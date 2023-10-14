/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** background.cpp
*/

#include <unordered_map>

#include "ECS/Components/BackgroundComponent.hpp"
#include "ECS/Containers/Registry.hpp"
#include "ECS/Containers/zipper/IndexedZipper.hpp"
#include "ECS/Systems/background.hpp"
#include "Assets/AssetLoader.hpp"
#include "client/display/Display.hpp"


namespace ECS::Systems {

    void background(
        [[maybe_unused]] Containers::Registry &registry,
        Containers::SparseArray<Components::BackgroundComponent> &backgrounds
    )
    {
        Screen::Display::beginDrawCamera();
        for (auto &&[eId, background] : Containers::IndexedZipper(backgrounds)) {
            background->position.x -= background->paralaxSpeed;
            if(background->position.x <= (-(background->texture.width) * background->frameScale)) {
                background->position.x = 0;
            }
            DrawTextureEx(background->texture,
            (Vector2) {background->position.x, 0},
            (float) 0.0, background->frameScale, WHITE);
            DrawTextureEx(background->texture,
            (Vector2) {background->texture.width * background->frameScale + background->position.x, 0},
            (float) 0.0, background->frameScale, WHITE);
        }
        Screen::Display::endDrawCamera();
    }

}; // namespace ECS::Systems
