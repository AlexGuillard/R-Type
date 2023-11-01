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

    void bydoShootingAI(
        Containers::Registry &registry,
        Containers::SparseArray<Components::BydoShootingAIComponent> &AIs,
        Containers::SparseArray<Components::TargetComponent> &targets,
        Containers::SparseArray<Components::InRangeComponent> &inRange,
        Containers::SparseArray<Components::TeamComponent> &teams,
        Containers::SparseArray<Components::PositionComponent> &positions
    )
    {
        for (auto &&[eId, ai, target, inRange, position]
            : Containers::IndexedZipper(AIs, targets, inRange, positions)) {
            ai->_shootCooldownTimer = max(
                0.,
                ai->_shootCooldownTimer - GameEngine::GameEngine::getDeltaTime());
            if (ai->_shootCooldownTimer == 0 && target->targetId != ECS::NullEntity()) {
                registry.emplaceComponent<Components::BydoShotComponent>(
                    registry.entityFromIndex(eId),
                    /* damage */ 1,
                    /* speed */ ai->shotSpeed,
                    /* xDirection */ target->dX / target->distance,
                    /* yDirection */ target->dY / target->distance
                );
                GameEngine::Events::push(GameEngine::Events::Type::BYDO_SHOOT, eId);
                ai->_shootCooldownTimer = ai->shootCooldown;
                target->targetId = ECS::NullEntity();
            }
        }
    }
} // namespace ECS::Systems
