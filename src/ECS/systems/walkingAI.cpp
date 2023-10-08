/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** walkingAI
*/

#include "ECS/Systems/walkingAI.hpp"
#include "ECS/Containers/zipper/Zipper.hpp"

namespace ECS::Systems {
    void walkingAI(
        Containers::Registry &registry,
        Containers::SparseArray<Components::WalkingAIComponent> &walkingAIs,
        Containers::SparseArray<Components::TargetComponent> &targets,
        Containers::SparseArray<Components::VelocityComponent> &velocities,
        Containers::SparseArray<Components::CollisionComponent> &allCollisions,
        Containers::SparseArray<Components::PositionComponent> &positions,
        Containers::SparseArray<Components::HitBoxComponent> &hitBoxes)
    {
        for (auto &&[walkingAI, target, velocity, position, hitBox] : Containers::Zipper(walkingAIs, targets, velocities positions, hitBoxes)) {
            if (target->distance > walkingAI->preferredDistance.first &&
                target->distance < walkingAI->preferredDistance.second) {
                velocity->x = 0;
                continue;
            }
            int direction = (target->dX > 0 ? 1 : -1) * (target->distance > walkingAI->preferredDistance.second ? 1 : -1);
            velocity->x = walkingAI->speed * direction;
        }
    }

}; // namespace ECS::Systems
