/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** shooting
*/

#include <string>
#include <cstring>
#include <sys/types.h>
#include <cstdint>

#include <raylib.h>

#include "ECS/Systems/shooting.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Components/DamageComponent.hpp"
#include "ECS/Components/HPComponent.hpp"
#include "ECS/Components/DrawableComponent.hpp"
#include "ECS/Containers/zipper/IndexedZipper.hpp"
#include "ECS/Creator.hpp"
#include "Assets/generatedAssets.hpp"

namespace ECS::Systems {

    static void shootBydoMissiles(
        Containers::Registry &registry,
        Containers::SparseArray<Components::BydoShotComponent> &bydoShotRequests
    )
    {
        auto &&positions = registry.getComponents<Components::PositionComponent>();
        for (auto &&[eId, request] : Containers::IndexedZipper(bydoShotRequests)) {
            if (!positions[eId]) { continue; }
            ECS::Creator::createBydoShot(
                registry,
                positions[eId]->x,
                positions[eId]->y,
                request->xDirection * request->speed,
                request->yDirection * request->speed,
                request->team
            );
            registry.removeComponent<Components::BydoShotComponent>(registry.entityFromIndex(eId));
        }
    }

    void shooting(
        Containers::Registry &registry,
        Containers::SparseArray<Components::MissileComponent> &missileRequests,
        Containers::SparseArray<Components::WaveBeamComponent> &waveBeamRequests,
        Containers::SparseArray<Components::BydoShotComponent> &bydoShotRequests
    )
    {
        shootBydoMissiles(registry, bydoShotRequests);
    }
}; // namespace ECS::Systems
