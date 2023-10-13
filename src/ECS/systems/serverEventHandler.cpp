/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** serverMovement
*/

#include <unordered_map>

#include "ECS/Systems/serverEventHandler.hpp"
#include "GameEngine/Events.hpp"
#include "Player/utils.hpp"

namespace ECS::Systems {
    void serverEventHandler(
        Containers::Registry &registry,
        Containers::SparseArray<Components::PositionComponent> &positions,
        Containers::SparseArray<Components::VelocityComponent> &velocities)
    {
        GameEngine::Events::Type event;
        int entityId = 0;

        while (GameEngine::Events::poll(event, entityId)) {
            ECS::Entity entity = registry.entityFromIndex(entityId);
            switch (event) {
            case GameEngine::Events::Type::PLAYER_UP:
                Player::movePlayer(velocities[entity]->x, velocities[entity]->y, true, false, false, false);
                break;
            case GameEngine::Events::Type::PLAYER_DOWN:
                Player::movePlayer(velocities[entity]->x, velocities[entity]->y, false, true, false, false);
                break;
            case GameEngine::Events::Type::PLAYER_LEFT:
                Player::movePlayer(velocities[entity]->x, velocities[entity]->y, false, false, true, false);
                break;
            case GameEngine::Events::Type::PLAYER_RIGHT:
                Player::movePlayer(velocities[entity]->x, velocities[entity]->y, false, false, false, true);
                break;
            default:
                break;
            }
        }
    }
} // namespace ECS::Systems
