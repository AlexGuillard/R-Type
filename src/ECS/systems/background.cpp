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
#include "ECS/Systems/Helper/BackgroundDrawer.hpp"
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
            Helper::BackgroundDrawer drawer(
                Assets::AssetLoader::loadTexturePng(background->spriteSheetIndex),
                background->frameScale
            );
            drawer.draw(background->position);
        }
        Screen::Display::endDrawCamera();
    }

}; // namespace ECS::Systems
