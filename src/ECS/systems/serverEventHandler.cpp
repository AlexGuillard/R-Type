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
        float up = 0.F;
        float down = 0.F;
        float left = 0.F;
        float right = 0.F;
    };

    /**
     * @brief Applies the velocity to the position by using the inputs of the
     * player and staying in sync with the client.
     * @param registry The ECS registry containing all entities and their components.
     * @param inputs Inputs of the player.
     * @param dt Delta time on the server.
    */
    static void applyVelocity(
        Containers::Registry &registry,
        int entityId,
        const PlayerInput &inputs)
    {
        const float dt = GameEngine::GameEngine::getDeltaTime();
        const float clientDt = 1. / Constants::frameRate;
        const float rateDiff = dt / clientDt;
        auto &&positions = registry.getComponents<ECS::Components::PositionComponent>();
        auto &&hitboxes = registry.getComponents<ECS::Components::HitBoxComponent>();
        auto &&collidables = registry.getComponents<ECS::Components::CollidableComponent>();
        auto &&collisions = registry.getComponents<ECS::Components::CollisionComponent>();
        auto &&solids = registry.getComponents<ECS::Components::SolidComponent>();
        auto &&velocities = registry.getComponents<ECS::Components::VelocityComponent>();
        auto &&teams = registry.getComponents<ECS::Components::TeamComponent>();

        if (!velocities[entityId]) {
            return;
        }
        if (rateDiff != 0) {
            velocities[entityId]->x = (inputs.right - inputs.left) * Constants::playerSpeed / rateDiff;
            velocities[entityId]->y = (inputs.down - inputs.up) * Constants::playerSpeed / rateDiff;
        }
        ECS::Systems::collision(registry, positions, velocities, hitboxes, collidables, collisions);
        ECS::Systems::solid(registry, solids, hitboxes, collisions, positions, velocities, teams);
        ECS::Systems::movement(registry, positions, velocities);
        velocities[entityId]->x = 0;
        velocities[entityId]->y = 0;
    }

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
            using enum GameEngine::Events::Type;
            case PLAYER_UP:
                playerInputs[entityId].up++;
                break;
            case PLAYER_DOWN:
                playerInputs[entityId].down++;
                break;
            case PLAYER_LEFT:
                playerInputs[entityId].left++;
                break;
            case PLAYER_RIGHT:
                playerInputs[entityId].right++;
                break;
            case PLAYER_SHOOT:
                if (teams[entityId] && positions[entityId]) {
                    ECS::Creator::createMissile(registry, registry.spawnEntity(), positions[entityId]->x, positions[entityId]->y, teams[entityId]->team);
                }
                break;
            default:
                break;
            }
        }
        for (const auto &[id, inputs] : playerInputs) {
            if (positions[id] && velocities[id]) {
                applyVelocity(registry, id, inputs);
            }
        }
    }
} // namespace ECS::Systems
