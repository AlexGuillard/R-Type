/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** serverMovement
*/

#include <unordered_map>
#include <vector>

#include "enums.hpp"
#include "server/network/sendCode.hpp"
#include "ECS/Containers/Registry.hpp"
#include "server/network/ServerNetwork.hpp"
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

namespace Network {
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
        ECS::Containers::Registry &registry,
        int entityId,
        const PlayerInput &inputs)
    {
        const float dt = (float)GameEngine::GameEngine::getDeltaTime();
        const float clientDt = 1.F / Constants::frameRate;
        const float rateDiff = dt / clientDt;
        auto &&positions = registry.getComponents<ECS::Components::PositionComponent>();
        auto &&hitboxes = registry.getComponents<ECS::Components::HitBoxComponent>();
        auto &&collidables = registry.getComponents<ECS::Components::CollidableComponent>();
        auto &&collisions = registry.getComponents<ECS::Components::CollisionComponent>();
        auto &&solids = registry.getComponents<ECS::Components::SolidComponent>();
        auto &&velocities = registry.getComponents<ECS::Components::VelocityComponent>();
        auto &&teams = registry.getComponents<ECS::Components::TeamComponent>();

        if (!velocities[entityId] || !positions[entityId]) {
            return;
        }
        if (rateDiff != 0) {
            velocities[entityId]->x = (inputs.right - inputs.left) * Constants::playerSpeed / rateDiff;
            velocities[entityId]->y = (inputs.down - inputs.up) * Constants::playerSpeed / rateDiff;
        }
        ECS::Systems::collision(registry, positions, velocities, hitboxes, collidables, collisions);
        ECS::Systems::solid(registry, solids, hitboxes, collisions, positions, velocities, teams);
        ECS::Systems::movement(registry, *positions[entityId], *velocities[entityId]);
        velocities[entityId]->x = 0;
        velocities[entityId]->y = 0;
    }

    void ServerNetwork::serverEventHandler(
        ECS::Containers::Registry &registry,
        ECS::Containers::SparseArray<ECS::Components::PositionComponent> &positions,
        ECS::Containers::SparseArray<ECS::Components::VelocityComponent> &velocities,
        ECS::Containers::SparseArray<ECS::Components::TeamComponent> &teams)
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
                    std::size_t eId = ECS::Creator::createMissile(registry, registry.spawnEntity(), positions[entityId]->x, positions[entityId]->y, teams[entityId]->team);

                    auto &&dataPositions = _engine.getRegistry(GameEngine::registryTypeEntities).getComponents<ECS::Components::PositionComponent>();
                    auto &&dataVelocity = _engine.getRegistry(GameEngine::registryTypeEntities).getComponents<ECS::Components::VelocityComponent>();
                    std::string res = "";
                    int pos[2] = {(int)positions[entityId]->x, (int)positions[entityId]->y};
                    int velocity[2] = {(int)velocities[entityId]->x, (int)velocities[entityId]->y};
                    Enums::TeamGroup team = teams[entityId]->team;

                    _dataToSend.append(Send::makeHeader((int)Enums::RFCCode::SPAWN_PLAYER_MISSILE, eId));
                    _dataToSend.append(Send::makeBodyMissile(pos, velocity, team, 1));
                    _dataToSend.append(Send::makeBodyNum((int)Enums::RFCCode::SPAWN_PLAYER_MISSILE));
                    for (const auto &pair : _listUdpEndpoints) {
                        const boost::asio::ip::udp::endpoint &endpoint = pair.second;
                        _asyncSocket.send_to(boost::asio::buffer(_dataToSend.c_str(), _dataToSend.length()), endpoint);
                    }
                    _dataToSend.clear();
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
} // namespace Network::ServerNetwork
