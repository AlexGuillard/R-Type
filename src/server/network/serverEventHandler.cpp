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
#include "ECS/Components/BydoShotComponent.hpp"
#include "ECS/Components/MissileComponent.hpp"
#include "ECS/Creator.hpp"

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

    void ServerNetwork::_shootMissile(
        ECS::Containers::Registry &registry,
        const ECS::Components::PositionComponent &position,
        const Enums::TeamGroup team,
        const float xVelocity,
        const float yVelocity
    )
    {
        int eId = ECS::Creator::createMissile(registry, registry.spawnEntity(), position.x, position.y, team);
        auto &&dataPositions = _engine.getRegistry(GameEngine::registryTypeEntities).getComponents<ECS::Components::PositionComponent>();
        auto &&dataVelocity = _engine.getRegistry(GameEngine::registryTypeEntities).getComponents<ECS::Components::VelocityComponent>();
        std::string res = "";

        res = Send::codeMissile({(int)Enums::RFCCode::SPAWN_PLAYER_MISSILE, eId}, {position.x, position.y}, {xVelocity, 0}, team, 0);
        for (const auto &[_, endpoint] : _listUdpEndpoints) {
            _asyncSocket.send_to(boost::asio::buffer(res.c_str(), res.length()), endpoint);
        }
        res.clear();
    }

    void ServerNetwork::_shootBydoShot(
        ECS::Containers::Registry &registry,
        int entityId,
        const ECS::Components::PositionComponent &position,
        const Enums::TeamGroup team
    )
    {
        auto &&positions = registry.getComponents<ECS::Components::PositionComponent>();
        auto &&velocities = registry.getComponents<ECS::Components::VelocityComponent>();
        auto &&bydoShotRequest = registry.getComponent<ECS::Components::BydoShotComponent>(registry.entityFromIndex(entityId));
        if (!bydoShotRequest) { return; };
        std::array<float, 2> pos = { position.x, position.y };
        std::array<float, 2> vel = { bydoShotRequest->xDirection * bydoShotRequest->speed, bydoShotRequest->yDirection * bydoShotRequest->speed};
        std::size_t eId = ECS::Creator::createBydoShot(registry, pos[0], pos[1], vel[0], vel[1]);
        std::array<int, 2> header({ (int)Enums::RFCCode::SPAWN_BYDO_SHOT, (int)eId });
        std::string res = Send::codeMissile(header, pos, vel, team, 0);

        for (const auto &[_, endpoint] : _listUdpEndpoints) {
            _asyncSocket.send_to(boost::asio::buffer(res.c_str(), res.length()), endpoint);
        }
        registry.removeComponent<ECS::Components::BydoShotComponent>(registry.entityFromIndex(entityId));
    }

    void ServerNetwork::_shootWaveBeam(
        ECS::Containers::Registry &registry,
        const ECS::Components::PositionComponent &position,
        const ECS::Components::VelocityComponent &velocity,
        const Enums::TeamGroup team,
        const int strength
    )
    {
        int eId = ECS::Creator::createMissile(registry, registry.spawnEntity(), position.x, position.y, team);
        auto &&dataPositions = _engine.getRegistry(GameEngine::registryTypeEntities).getComponents<ECS::Components::PositionComponent>();
        auto &&dataVelocity = _engine.getRegistry(GameEngine::registryTypeEntities).getComponents<ECS::Components::VelocityComponent>();
        std::string res = "";

        res = Send::codeMissile({(int)Enums::RFCCode::SPAWN_WAVE_BEAM, eId}, {position.x, position.y}, {velocity.x, velocity.y}, team, strength);
        for (const auto &[_, endpoint] : _listUdpEndpoints) {
            _asyncSocket.send_to(boost::asio::buffer(res.c_str(), res.length()), endpoint);
        }
        res.clear();
    }

    void ServerNetwork::_shootWaveBeam(
        ECS::Containers::Registry &registry,
        const ECS::Components::WaveBeamComponent &waveInfo)
    {
        ECS::Components::PositionComponent position(waveInfo.x, waveInfo.y);
        ECS::Components::VelocityComponent velocity(0, 0);
        _shootWaveBeam(registry, position, velocity, waveInfo.team, waveInfo.strength);
    }

    void ServerNetwork::serverEventHandler(
        ECS::Containers::Registry &registry,
        ECS::Containers::SparseArray<ECS::Components::PositionComponent> &positions,
        ECS::Containers::SparseArray<ECS::Components::VelocityComponent> &velocities,
        ECS::Containers::SparseArray<ECS::Components::TeamComponent> &teams,
        ECS::Containers::SparseArray<ECS::Components::WaveBeamComponent> &waveBeamsInfos)
    {
        GameEngine::Events::Type event;
        int entityId = 0;
        std::unordered_map<int, PlayerInput> playerInputs;
        // id -> (isHeld, timeHeld)
        static std::unordered_map<int, std::pair<bool, float>> timeSinceShootHeld;

        resetHeldInfo(timeSinceShootHeld);
        while (GameEngine::Events::poll(event, entityId)) {
            ECS::Entity entity = registry.entityFromIndex(entityId);
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
            case BYDO_SHOOT_MISSILE:
                if (positions[entityId] && velocities[entityId] && teams[entityId]) {
                    this->_shootBydoShot(
                        registry, entityId, *positions[entityId], teams[entityId]->team
                    );
                }
                break;
            case BYDO_SHOOT_WAVE_BEAM:
                if (positions[entityId] && velocities[entityId] && teams[entityId] && waveBeamsInfos[entityId]) {
                    this->_shootWaveBeam(
                        registry, *waveBeamsInfos[entityId]
                    );
                }
                break;
            case POD_SHOOT:
                if (positions[entity] && velocities[entity] && teams[entity] && registry.getComponent<ECS::Components::MissileComponent>(entity)) {
                    this->_shootMissile(
                        registry, *positions[entity], teams[entity]->team, Constants::waveBeamSpeed
                    );
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
            if (timeHeld > 0 && positions[id] && velocities[id] && teams[id]) {
                if (timeHeld < Constants::timeNeededForWaveBeam) {
                    this->_shootMissile(
                        registry, *positions[id], teams[id]->team, Constants::waveBeamSpeed
                    );
                } else {
                    this->_shootWaveBeam(
                        registry, *positions[id], *velocities[id], teams[id]->team, Player::calculateWaveBeamStrength(timeHeld)
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
