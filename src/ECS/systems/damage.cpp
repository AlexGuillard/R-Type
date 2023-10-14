/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** damage
*/

#include <raylib.h>
#include "ECS/Systems/damage.hpp"
#include "ECS/Components/GravityComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Containers/zipper/Zipper.hpp"
#include "ECS/Containers/zipper/IndexedZipper.hpp"

namespace ECS::Systems {

    void damage(
        [[maybe_unused]] Containers::Registry &registry,
        ECS::Containers::SparseArray<ECS::Components::CollisionComponent> &collision,
        ECS::Containers::SparseArray<ECS::Components::DamageComponent> &damage,
        ECS::Containers::SparseArray<ECS::Components::TeamComponent> &teams,
        ECS::Containers::SparseArray<ECS::Components::HPComponent> &hpComponents)
    {
        std::vector<std::size_t> toDelete;

        for (auto &&[entityId, hpComponent, collision] : Containers::IndexedZipper(hpComponents, collision)) {
            auto &&team = teams.at(entityId);
            for (auto eId : collision->collisions) {
                if (!team || !teams.at(eId) || teams.at(eId)->team != team->team) {
                    if (!damage.at(eId)) { continue; } // ignore entities that can't damage
                    std::size_t damageOther = damage.at(eId)->damage;
                    std::size_t hpEntity = hpComponents.at(entityId)->hp;
                    if (hpEntity == 0 || hpEntity <= damageOther) {
                        // store the entity to allow mutual destruction
                        toDelete.push_back(entityId);
                        break;
                    }
                    hpComponents.at(entityId)->hp -= damageOther;
                }
            }
        }
        for (auto &&entityId : toDelete) {
            registry.killEntity(registry.entityFromIndex(entityId));
        }
    }

}; // namespace ECS::systems
