/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** bydoShootingAI
*/

#include "ECS/Systems/bydoShootingAI.hpp"
#include "ECS/Containers/zipper/IndexedZipper.hpp"
#include "ECS/Creator.hpp"
#include "ECS/Components/BydoShotComponent.hpp"
#include "ECS/Components/WaveBeamComponent.hpp"
#include "ECS/Components/MissileSpawnPointComponent.hpp"
#include "ECS/Components/HitBoxComponent.hpp"
#include "ECS/Systems/target.hpp"
#include "GameEngine/GameEngine.hpp"
#include "GameEngine/Events.hpp"
#include "enums.hpp"
#include "constants.hpp"
#include "ECS/Entity.hpp"

namespace ECS::Systems {
    template<typename T>
    T max(T a, T b)
    {
        return (a > b ? a : b);
    }

    static void shootFromSpawnPoint(
        Containers::Registry &registry,
        std::size_t eId,
        std::size_t spawnPointIdx,
        Components::MissileSpawnPointComponent &spawnPoints,
        Components::PositionComponent &position,
        Utils::Vector2 spawnPointPosition,
        Components::HitBoxComponent &hitBox,
        Components::BydoShootingAIComponent &ai,
        Components::TargetComponent &target,
        std::optional<Components::TeamComponent> &team
    )
    {
        float x = position.x + spawnPointPosition.x * hitBox.width;
        float y = position.y + spawnPointPosition.y * hitBox.height;

        Enums::ShotType type = std::get<1>(spawnPoints.spawnPoints[spawnPointIdx]);
        spawnPoints.currentSpawnPoint = spawnPointIdx;
        switch (type) {
        case Enums::ShotType::BYDO_SHOT:
            updateTarget(registry, eId, target, position, registry.getComponents<Components::PositionComponent>());
            registry.emplaceComponent<Components::BydoShotComponent>(
                registry.entityFromIndex(eId),
                /* damage */ 1,
                /* speed */ ai.shotSpeed,
                /* position */ Utils::Vector2(x, y),
                /* direction */ Utils::Vector2(target.dX / target.distance, target.dY / target.distance)
            );
            GameEngine::Events::push(GameEngine::Events::Type::BYDO_SHOOT_MISSILE, eId);
            break;
        case Enums::ShotType::WAVE_BEAM:
            registry.emplaceComponent<Components::WaveBeamComponent>(
                registry.entityFromIndex(eId),
                /* x */ x,
                /* y */ y,
                /* team */ team ? team->team : Enums::TeamGroup::ENEMY,
                /* damage */ 1,
                /* strength */ 5
            );
            GameEngine::Events::push(GameEngine::Events::Type::BYDO_SHOOT_WAVE_BEAM, eId);
            break;
        default:
            break;
        }
    }

    void bydoShootingAI(
        Containers::Registry &registry,
        Containers::SparseArray<Components::BydoShootingAIComponent> &AIs,
        Containers::SparseArray<Components::TargetComponent> &targets,
        Containers::SparseArray<Components::InRangeComponent> &inRange,
        Containers::SparseArray<Components::TeamComponent> &teams,
        Containers::SparseArray<Components::PositionComponent> &positions
    )
    {
        auto &&allSpawnPoints = registry.getComponents<Components::MissileSpawnPointComponent>();
        auto &&hitBoxes = registry.getComponents<Components::HitBoxComponent>();

        for (auto &&[eId, ai, target, inRange, position]
            : Containers::IndexedZipper(AIs, targets, inRange, positions)) {
            if (allSpawnPoints[eId] && hitBoxes[eId]) {
                bool hasShot = false;
                Components::MissileSpawnPointComponent &spawnPoints = *allSpawnPoints[eId];
                Components::HitBoxComponent &hitBox = *hitBoxes[eId];
                int i = 0;
                for (auto &&[spawnPointPosition, shotType, cooldown, timer] : spawnPoints.spawnPoints) {
                    timer -= GameEngine::GameEngine::getDeltaTime();
                    if (timer <= 0) {
                        hasShot = true;
                        timer = cooldown;
                        shootFromSpawnPoint(
                            registry,
                            eId,
                            i,
                            spawnPoints,
                            *position,
                            spawnPointPosition,
                            hitBox,
                            *ai,
                            *target,
                            teams[eId]
                        );
                    }
                    i++;
                }
            } else {
                ai->_shootCooldownTimer = max(
                    0.,
                    ai->_shootCooldownTimer - GameEngine::GameEngine::getDeltaTime());
                if (ai->_shootCooldownTimer == 0 && target->targetId != ECS::NullEntity()) {
                    if (ai->shotType == Enums::ShotType::BYDO_SHOT) {
                        registry.emplaceComponent<Components::BydoShotComponent>(
                            registry.entityFromIndex(eId),
                            /* damage */ 1,
                            /* speed */ ai->shotSpeed,
                            /* position */ Utils::Vector2(position->x, position->y),
                            /* direction */ Utils::Vector2(target->dX / target->distance, target->dY / target->distance)
                        );
                        GameEngine::Events::push(GameEngine::Events::Type::BYDO_SHOOT_MISSILE, eId);
                    } else if (ai->shotType == Enums::ShotType::WAVE_BEAM) {
                        registry.emplaceComponent<Components::WaveBeamComponent>(
                            registry.entityFromIndex(eId),
                            /* x */ position->x,
                            /* y */ position->y,
                            /* team */ teams[eId] ? teams[eId]->team : Enums::TeamGroup::ENEMY,
                            /* damage */ 1,
                            /* strength */ 5
                        );
                        GameEngine::Events::push(GameEngine::Events::Type::BYDO_SHOOT_WAVE_BEAM, eId);
                    }
                    ai->_shootCooldownTimer = ai->shootCooldown;
                    target->targetId = ECS::NullEntity();
                }
            }
        }
    }
} // namespace ECS::Systems
