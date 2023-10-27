/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** serverMovement
*/

#include <unordered_map>
#include <vector>

#include "ECS/Systems/serverEventHandler.hpp"
#include "GameEngine/Events.hpp"
#include "GameEngine/GameEngine.hpp"
#include "Player/utils.hpp"
#include "ECS/Creator.hpp"
#include "constants.hpp"
#include "ECS/Systems/collision.hpp"
#include "ECS/Systems/movement.hpp"
#include "ECS/Systems/solid.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/HitBoxComponent.hpp"
#include "ECS/Components/CollisionComponent.hpp"
#include "ECS/Components/CollidableComponent.hpp"
#include "ECS/Components/SolidComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Components/TeamComponent.hpp"

#include <iostream>

namespace ECS::Systems {
    struct PlayerInput {
        std::size_t up = 0;
        std::size_t down = 0;
        std::size_t left = 0;
        std::size_t right = 0;
    };
    void serverEventHandler(
        Containers::Registry &registry,
        Containers::SparseArray<Components::PositionComponent> &positions,
        Containers::SparseArray<Components::VelocityComponent> &velocities,
        Containers::SparseArray<Components::TeamComponent> &teams)
    {
        GameEngine::Events::Type event;
        int entityId = 0;
        std::unordered_map<int, PlayerInput> playerInputs;

        while (GameEngine::Events::poll(event, entityId)) {
            switch (event) {
            case GameEngine::Events::Type::PLAYER_UP:
                playerInputs[entityId].up++;
                break;
            case GameEngine::Events::Type::PLAYER_DOWN:
                playerInputs[entityId].down++;
                break;
            case GameEngine::Events::Type::PLAYER_LEFT:
                playerInputs[entityId].left++;
                break;
            case GameEngine::Events::Type::PLAYER_RIGHT:
                playerInputs[entityId].right++;
                break;
            case GameEngine::Events::Type::PLAYER_SHOOT:
                ECS::Creator::createMissile(registry, registry.spawnEntity(), positions[entityId]->x, positions[entityId]->y, teams[entityId]->team);
                break;
            default:
                break;
            }
        }
        for (auto &[entityId, input] : playerInputs) {
            if (positions[entityId] && velocities[entityId]) {
                auto &&positions = registry.getComponents<ECS::Components::PositionComponent>();
                auto &&hitboxes = registry.getComponents<ECS::Components::HitBoxComponent>();
                auto &&collidables = registry.getComponents<ECS::Components::CollidableComponent>();
                auto &&collisions = registry.getComponents<ECS::Components::CollisionComponent>();
                auto &&solids = registry.getComponents<ECS::Components::SolidComponent>();
                auto &&velocities = registry.getComponents<ECS::Components::VelocityComponent>();
                auto &&teams = registry.getComponents<ECS::Components::TeamComponent>();
                auto &input = playerInputs[entityId];

                Player::updateVelocity(velocities[entityId]->x, velocities[entityId]->y, input.up, input.down, input.left, input.right);
                ECS::Systems::collision(registry, positions, velocities, hitboxes, collidables, collisions);
                ECS::Systems::solid(registry, solids, hitboxes, collisions, positions, velocities, teams);
                ECS::Systems::movement(registry, positions, velocities);
            }
            if (velocities[entityId]) {
                velocities[entityId]->x = 0;
                velocities[entityId]->y = 0;
            }
        }
    }
} // namespace ECS::Systems
