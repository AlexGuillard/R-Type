/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** target
*/

#include <cmath>

#include "GameEngine/GameEngine.hpp"
#include "ECS/Systems/target.hpp"
#include "ECS/Containers/zipper/Zipper.hpp"

namespace ECS::Systems {
    void target(
        Containers::Registry &registry,
        Containers::SparseArray<Components::TargetComponent> &targets,
        Containers::SparseArray<Components::PositionComponent> &positions)
    {
        for (auto &&[target, position] : Containers::Zipper(targets, positions)) {
            if (target->targetId == ECS::NullEntity()) { continue; }
            auto &targetPosition = positions[target->targetId];
            if (!targetPosition.has_value()) { continue; }
            target->dX = targetPosition->x - position->x;
            target->dY = targetPosition->y - position->y;
            target->distance = std::sqrt(std::pow(target->dX, 2) + std::pow(target->dY, 2));
            target->t += GameEngine::GameEngine::getDeltaTime();
        }
    }
}
