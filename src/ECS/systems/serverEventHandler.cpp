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
    struct PlayerInput {
        std::size_t up = 0;
        std::size_t down = 0;
        std::size_t left = 0;
        std::size_t right = 0;
    };
    void serverEventHandler(
        Containers::Registry &registry,
        Containers::SparseArray<Components::PositionComponent> &positions,
        Containers::SparseArray<Components::VelocityComponent> &velocities)
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
            default:
                break;
            }
        }
        for (auto &[entityId, input] : playerInputs) {
            Player::updateVelocity(velocities[entityId]->x, velocities[entityId]->y, input.up, input.down, input.left, input.right);
        }
    }
} // namespace ECS::Systems
