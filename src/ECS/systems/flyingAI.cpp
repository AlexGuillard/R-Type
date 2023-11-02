/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** FlyingAI
*/

#include "ECS/Systems/flyingAI.hpp"
#include "ECS/Containers/zipper/IndexedZipper.hpp"
#include "ECS/Components/InRangeComponent.hpp"

template <typename T>
static T abs(T value)
{
    return value < 0 ? -value : value;
}

template <typename T>
static bool inRange(T value, std::pair<T, T> range)
{
    return (
        value >= range.first && value <= range.second ||
        value >= range.second && value <= range.first
        );
}

void ECS::Systems::flyingAI(
    Containers::Registry &registry,
    Containers::SparseArray<Components::FlyingAIComponent> &AIs,
    Containers::SparseArray<Components::TargetComponent> &targets,
    Containers::SparseArray<Components::PositionComponent> &positions,
    Containers::SparseArray<Components::VelocityComponent> &velocities)
{
    for (auto &&[eId, ai, target, position, velocity] : ECS::Containers::IndexedZipper(
        AIs,
        targets,
        positions,
        velocities
    )) {
        ECS::Entity entity = registry.entityFromIndex(eId);
        if (
            inRange(target->dX, ai->preferedXDistance) &&
            inRange(target->dY, ai->preferedYDistance)
            ) {
            registry.emplaceComponent<ECS::Components::VelocityComponent>(entity, 0, 0);
            registry.emplaceComponent<ECS::Components::InRangeComponent>(entity);
            continue;
        }
        registry.removeComponent<ECS::Components::InRangeComponent>(entity);
        if (target->dX < ai->preferedXDistance.first) {
            velocity->x = -ai->speed;
        } else if (target->dX > ai->preferedXDistance.second) {
            velocity->x = ai->speed;
        } else {
            velocity->x = 0;
        }
        if (target->dY < ai->preferedYDistance.first) {
            velocity->y = -ai->speed;
        } else if (target->dY > ai->preferedYDistance.second) {
            velocity->y = ai->speed;
        } else {
            velocity->y = 0;
        }
    }
}
