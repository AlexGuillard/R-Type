/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** walkingAI
*/

#include "ECS/Systems/walkingAI.hpp"
#include "ECS/Containers/zipper/IndexedZipper.hpp"
#include "ECS/Components/InRangeComponent.hpp"

namespace ECS::Systems {
    /**
     * @brief Check if entity that has position and hitBox is colliding with
     * entityId from bottom
     * @param registry Registry
     * @param entityId Entity we are colliding with
     * @param position Our position
     * @param hitBox Our hitBox
     * @return true if colliding from bottom, false otherwise
     */
    static bool isBottomCollision(
        Containers::Registry &registry,
        const Entity &entityId,
        Components::PositionComponent &position,
        Components::HitBoxComponent &hitBox)
    {
        auto &entityPosition = *registry.getComponent<Components::PositionComponent>(entityId);
        auto &entityHitBox = *registry.getComponent<Components::HitBoxComponent>(entityId);
        // amount of overlap on our left side
        int overlapLeft = (entityPosition.x + entityHitBox.width) - position.x;
        // amount of overlap on our right side
        int overlapRight = (position.x + hitBox.width) - entityPosition.x;
        // amount of overlap on our top side
        int overlapTop = (entityPosition.y + entityHitBox.height) - position.y;
        // amount of overlap on our bottom side
        int overlapBottom = (position.y + hitBox.height) - entityPosition.y;

        // if overlap bottom is smallest, collision is from bottom
        if (overlapBottom < overlapTop && overlapBottom < overlapLeft && overlapBottom < overlapRight) {
            return overlapBottom >= 0;
        }
        return false;
    }

    void walkingAI(
        Containers::Registry &registry,
        Containers::SparseArray<Components::WalkingAIComponent> &walkingAIs,
        Containers::SparseArray<Components::TargetComponent> &targets,
        Containers::SparseArray<Components::VelocityComponent> &velocities,
        Containers::SparseArray<Components::CollisionComponent> &allCollisions,
        Containers::SparseArray<Components::PositionComponent> &positions,
        Containers::SparseArray<Components::HitBoxComponent> &hitBoxes)
    {
        for (auto &&[eId, walkingAI, target, velocity, collisions, position, hitBox] : Containers::IndexedZipper(walkingAIs, targets, velocities, allCollisions, positions, hitBoxes)) {
            // check if collision with ground
            bool isOnGround = false;
            for (const ECS::Entity &entityId : collisions->collisions) {
                if (isBottomCollision(registry, entityId, *position, *hitBox)) {
                    isOnGround = true;
                    break;
                }
            }
            if (!isOnGround) { continue; }
            if (target->distance > walkingAI->preferredDistance.first &&
                target->distance < walkingAI->preferredDistance.second) {
                velocity->x = 0;
                registry.emplaceComponent<Components::InRangeComponent>(registry.entityFromIndex(eId));
                continue;
            }
            registry.removeComponent<Components::InRangeComponent>(registry.entityFromIndex(eId));
            int direction = (target->dX > 0 ? 1 : -1) * (target->distance > walkingAI->preferredDistance.second ? 1 : -1);
            velocity->x = walkingAI->speed * direction;
        }
    }

}; // namespace ECS::Systems
