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
        for (auto &&[entityId, hpComponent, team, collision] : Containers::IndexedZipper(hpComponents, teams, collision)) {
            for (auto eId : collision->collisions) {
                if(teams.at(eId)->team != teams.at(entityId)->team) {
                    std::size_t damageOther = damage.at(eId)->damage;
                    std::size_t hpEntity = hpComponents.at(entityId)->hp;
                    if (hpEntity == 0 || hpEntity <= damageOther) {
                        registry.killEntity(ECS::Containers::Registry::entityFromIndex(entityId));
                        break;
                    }
                    hpComponents.at(entityId)->hp -= damageOther;
                }
            }
        }
    }

}; // namespace ECS::systems
