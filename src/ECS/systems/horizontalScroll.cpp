/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** horizontalScroll
*/

#include "ECS/Systems/horizontalScroll.hpp"
#include "ECS/Containers/zipper/Zipper.hpp"
#include "GameEngine/GameEngine.hpp"

namespace ECS::Systems {

    void horizontalScroll(
        Containers::Registry &registry,
        ECS::Containers::SparseArray<ECS::Components::HorizontalScrollComponent> &horizontalScrolls,
        ECS::Containers::SparseArray<ECS::Components::PositionComponent> &positions)
    {
        for (auto &&[horizontalScroll, position]
            : Containers::Zipper(horizontalScrolls, positions)) {
            position->x -= horizontalScroll->speed * GameEngine::GameEngine::getDeltaTime();
        }
    }

} // namespace ECS::Systems
