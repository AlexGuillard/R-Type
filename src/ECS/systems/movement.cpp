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
#include "ECS/Containers/zipper/Zipper.hpp"

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
        for (auto &&[position, velocity] : Containers::Zipper(positions, velocities)) {
            movement(registry, *position, *velocity);
        }
    }

}; // namespace ECS::Systems
