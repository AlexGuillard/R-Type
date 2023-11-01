/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** movement
*/

#include "GameEngine/GameEngine.hpp"
#include "ECS/Systems/movement.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Containers/zipper/IndexedZipper.hpp"
#include "constants.hpp"

namespace ECS::Systems {

    void movement(
        [[maybe_unused]] Containers::Registry &registry,
        Components::PositionComponent &position,
        Components::VelocityComponent &velocity)
    {
        position.x += velocity.x * GameEngine::GameEngine::getDeltaTime();
        position.y += velocity.y * GameEngine::GameEngine::getDeltaTime();
    }

    void movement(
        [[maybe_unused]] Containers::Registry &registry,
        Containers::SparseArray<Components::PositionComponent> &positions,
        Containers::SparseArray<Components::VelocityComponent> &velocities)
    {
        std::vector<std::size_t> toDelete;
        for (auto &&[eId, position, velocity] : Containers::IndexedZipper(positions, velocities)) {
            movement(registry, *position, *velocity);

            if (position->x < -Constants::deathZone ||
                position->x >(Constants::cameraDefaultWidth + Constants::deathZone) ||
                position->y < -Constants::deathZone ||
                position->y >(Constants::cameraDefaultHeight + Constants::deathZone)) {
                toDelete.push_back(eId);
            }
        }
        for (auto &&entityId : toDelete) {
            registry.killEntity(registry.entityFromIndex(entityId));
        }
    }

}; // namespace ECS::Systems
