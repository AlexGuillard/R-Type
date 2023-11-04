/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** target
*/

#include <cmath>

#include "GameEngine/GameEngine.hpp"
#include "ECS/Systems/target.hpp"
#include "ECS/Containers/zipper/IndexedZipper.hpp"
#include "ECS/Components/MissileSpawnPointComponent.hpp"
#include "ECS/Components/HitBoxComponent.hpp"

namespace ECS::Systems {

    void updateTarget(
        Containers::Registry &registry,
        std::size_t eId,
        Components::TargetComponent &target,
        Components::PositionComponent &position,
        ECS::Containers::SparseArray<Components::PositionComponent> &positions)
    {
        auto &&spawnPoints = registry.getComponents<Components::MissileSpawnPointComponent>();
        auto &&hitBoxes = registry.getComponents<Components::HitBoxComponent>();
        if (target.targetId == ECS::NullEntity()) { return; }
        ECS::Entity targetEntity = registry.entityFromIndex(target.targetId);
        auto &targetPosition = positions[targetEntity];
        if (!targetPosition.has_value()) { return; }
        float x = position.x;
        float y = position.y;
        if (spawnPoints[eId] && hitBoxes[eId]) {
            std::size_t spawnPointIndex = spawnPoints[eId]->currentSpawnPoint;
            auto &&[dX, dY] = std::get<0>(spawnPoints[eId]->spawnPoints[spawnPointIndex]);
            x += dX * hitBoxes[eId]->width;
            y += dY * hitBoxes[eId]->height;
        }
        target.dX = targetPosition->x - x;
        target.dY = targetPosition->y - y;
        target.distance = std::sqrt(std::pow(target.dX, 2) + std::pow(target.dY, 2));
        target.t += GameEngine::GameEngine::getDeltaTime();
    }

    void target(
        Containers::Registry &registry,
        Containers::SparseArray<Components::TargetComponent> &targets,
        Containers::SparseArray<Components::PositionComponent> &positions)
    {
        for (auto &&[eId, target, position] : Containers::IndexedZipper(targets, positions)) {
            updateTarget(registry, eId, *target, *position, positions);
        }
    }
}
