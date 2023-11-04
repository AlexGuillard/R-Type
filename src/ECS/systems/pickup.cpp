/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** pickup
*/

#pragma once

#include "ECS/Systems/pickup.hpp"
#include "ECS/Components/ShootingTimerComponent.hpp"
#include "ECS/Containers/zipper/IndexedZipper.hpp"
#include "ECS/Components/FlyingAIComponent.hpp"
#include "ECS/Components/TargetComponent.hpp"
#include "ECS/Components/TeamComponent.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/HorizontalScrollComponent.hpp"

static void addPodAI(ECS::Containers::Registry &registry, ECS::Entity entity, ECS::Entity other,
    const ECS::Components::PickupComponent &pickup)
{
    auto &&team = registry.getComponent<ECS::Components::TeamComponent>(other);
    auto &&position = registry.getComponent<ECS::Components::PositionComponent>(other);

    registry.removeComponent<ECS::Components::HorizontalScrollComponent>(entity);
    registry.emplaceComponent<ECS::Components::FlyingAIComponent>(
        entity,
        std::make_pair(-50.F, 50.F),
        std::make_pair(25.F, 75.1F),
        100);
    registry.emplaceComponent<ECS::Components::TargetComponent>(entity, other);
    registry.emplaceComponent<ECS::Components::ShootingTimerComponent>(
        other, pickup.data.shootingTimer.shootCooldown, pickup.data.shootingTimer.shotType);
    if (team) {
        registry.emplaceComponent<ECS::Components::TeamComponent>(entity, team->team);
    }
    if (position) {
        registry.emplaceComponent<ECS::Components::PositionComponent>(entity, position->x, position->y - 50);
    }
}

void ECS::Systems::pickup(
    Containers::Registry &registry,
    Containers::SparseArray<Components::PickupComponent> &pickups,
    Containers::SparseArray<Components::CollisionComponent> &collisions)
{
    std::vector<ECS::Entity> collectedPickups;
    auto &&teams = registry.getComponents<ECS::Components::TeamComponent>();

    for (auto [entity, pickup, collision] : Containers::IndexedZipper(pickups, collisions)) {
        if (collision->collisions.empty()) { continue; }
        ECS::Entity other = *collision->collisions.begin();
        if (!teams[other] || teams[other]->team == Enums::TeamGroup::ENEMY || teams[other]->team == Enums::TeamGroup::NEUTRAL) { continue; }
        switch (pickup->type) {
        case Enums::PickupType::POD:
            addPodAI(registry, registry.entityFromIndex(entity), other, *pickup);
            collectedPickups.push_back(registry.entityFromIndex(entity));
            break;
        default:
            break;
        }
    }
    for (auto entity : collectedPickups) {
        registry.removeComponent<Components::PickupComponent>(entity);
    }
}
