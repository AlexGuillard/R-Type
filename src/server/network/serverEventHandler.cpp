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

    static void resetHeldInfo(std::unordered_map<int, std::pair<bool, float>> &timeSinceShootHeld)
    {
        for (auto &&[id, heldInfo] : timeSinceShootHeld) {
            auto &&[isHeld, _] = heldInfo;
            isHeld = false;
        }
    }

    static void shootMissile(
        GameEngine::GameEngine &_engine,
        ECS::Containers::Registry &registry,
        const ECS::Components::PositionComponent &position,
        ECS::Components::VelocityComponent &velocity,
        const Enums::TeamGroup &team,
        const std::unordered_map<std::string, boost::asio::ip::udp::endpoint> &listUdpEndpoints,
        boost::asio::ip::udp::socket &asyncSocket
    )
    {
        std::size_t eId = ECS::Creator::createMissile(registry, registry.spawnEntity(), position.x, position.y, team);
        auto &&dataPositions = _engine.getRegistry(GameEngine::registryTypeEntities).getComponents<ECS::Components::PositionComponent>();
        auto &&dataVelocity = _engine.getRegistry(GameEngine::registryTypeEntities).getComponents<ECS::Components::VelocityComponent>();
        std::string res = "";
        int pos[2] = { (int)position.x, (int)position.y };
        int vel[2] = { (int)velocity.x, (int)velocity.y };

        res.append(Send::makeHeader((int)Enums::RFCCode::SPAWN_PLAYER_MISSILE, eId));
        res.append(Send::makeBodyMissile(pos, vel, team, 1));
        res.append(Send::makeBodyNum((int)Enums::RFCCode::SPAWN_PLAYER_MISSILE));
        for (const auto &[_, endpoint] : listUdpEndpoints) {
            asyncSocket.send_to(boost::asio::buffer(res.c_str(), res.length()), endpoint);
        }
        res.clear();
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
        // id -> (isHeld, timeHeld)
        static std::unordered_map<int, std::pair<bool, float>> timeSinceShootHeld;

        resetHeldInfo(timeSinceShootHeld);
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
                if (timeSinceShootHeld.contains(entityId)) {
                    timeSinceShootHeld[entityId].second += GameEngine::GameEngine::getDeltaTime();
                    timeSinceShootHeld[entityId].first = true;
                } else {
                    timeSinceShootHeld.emplace(entityId, std::make_pair(true, 0.F));
                }
                break;
            default:
                break;
            }
        }
        std::vector<int> toDelete;
        for (auto &[id, heldInfo] : timeSinceShootHeld) {
            auto &[isHeld, timeHeld] = heldInfo;
            if (isHeld) { continue; } // only shoot when the button is released
            if (timeHeld > 0) {
                if (positions[id] && velocities[id] && teams[id]) {
                    shootMissile(
                        _engine, registry, *positions[id], *velocities[id],
                        teams[id]->team, _listUdpEndpoints, _asyncSocket
                    );
                }

                toDelete.push_back(id);
            }
        }
        for (const auto &id : toDelete) {
            timeSinceShootHeld.erase(id);
        }

        for (const auto &[id, inputs] : playerInputs) {
            if (positions[id] && velocities[id]) {
                applyVelocity(registry, id, inputs);
            }
        }
    }
} // namespace Network::ServerNetwork
