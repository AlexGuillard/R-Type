/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** collision
*/

#include "GameEngine/GameEngine.hpp"
#include "ECS/Systems/collision.hpp"
#include "ECS/Containers/zipper/IndexedZipper.hpp"
#include "ECS/Containers/SparseArray.hpp"

namespace ECS::Systems {
    /**
     * @brief Removes the collision component of entities that have no collision
     */
    static void removeEmptyCollisionComponents(
        Containers::Registry &registry,
        Containers::SparseArray<Components::CollisionComponent> &collisions)
    {
        for (auto &&[entityId, collision] : Containers::IndexedZipper(collisions)) {
            if (collision->collisions.empty()) {
                registry.removeComponent
                    <Components::CollisionComponent>(
                        registry.entityFromIndex(entityId)
                    );
            }
        }
    }

    /**
     * @brief Checks if two entities are colliding
    */
    static bool collidesWith(
        const Components::HitBoxComponent &receiverHitbox,
        const Components::PositionComponent &receiverPosition,
        const Components::HitBoxComponent &giverHitbox,
        const Components::PositionComponent &giverPosition)
    {
        return (
            (receiverPosition.x + receiverHitbox.width) >= giverPosition.x
            && receiverPosition.x <= (giverPosition.x + giverHitbox.width)
            && (receiverPosition.y + receiverHitbox.height) >= giverPosition.y
            && receiverPosition.y <= (giverPosition.y + giverHitbox.height)
            );
    }

    /**
     * @brief Adds an entity to the collision component of another entity.
     * Creates the collision component if it doesn't exist.
    */
    static void addToCollisionComponent(
        Containers::Registry &registry,
        std::optional<Components::CollisionComponent> &collision,
        const std::size_t receiverId,
        const std::size_t giverId)
    {
        if (!collision.has_value()) {
            collision = Components::CollisionComponent();
        }
        collision->collisions.insert(
            registry.entityFromIndex(giverId)
        );
    }

    /**
     * @brief Removes an entity from the collision component of another entity.
    */
    static void removeFromCollisionComponent(
        Containers::Registry &registry,
        std::optional<Components::CollisionComponent> &collision,
        const std::size_t receiverId,
        const std::size_t giverId)
    {
        if (collision.has_value()) {
            collision->collisions.erase(
                registry.entityFromIndex(giverId)
            );
        }
    }

    void collision(
        Containers::Registry &registry,
        Containers::SparseArray<Components::PositionComponent> &positions,
        Containers::SparseArray<Components::VelocityComponent> &velocities,
        Containers::SparseArray<Components::HitBoxComponent> &hitboxes,
        Containers::SparseArray<Components::CollidableComponent> &collidables,
        Containers::SparseArray<Components::CollisionComponent> &collisions)
    {
        removeEmptyCollisionComponents(registry, collisions);
        for (auto &&[receiverId, receiverPosition, receiverHitbox, receiverCollidable] : Containers::IndexedZipper(positions, hitboxes, collidables)) {
            // collision receiver
            for (auto &&[giverId, giverPosition, giverHitbox, giverCollidable] : Containers::IndexedZipper(positions, hitboxes, collidables)) {
                // collision giver
                if (receiverId == giverId) { continue; }
                    Components::PositionComponent receiverPositionCopy = *receiverPosition;
                    Components::VelocityComponent receiverVelocityCopy = velocities[receiverId].has_value() ? *velocities[receiverId] : Components::VelocityComponent(0, 0);
                    Components::PositionComponent giverPositionCopy = *giverPosition;
                    Components::VelocityComponent giverVelocityCopy = velocities[giverId].has_value() ? *velocities[giverId] : Components::VelocityComponent(0, 0);
                    for (std::size_t i = 0; i < 100; i++) {
                        receiverPositionCopy.x += (receiverVelocityCopy.x * GameEngine::GameEngine::getDeltaTime()) / 100.;
                        receiverPositionCopy.y += (receiverVelocityCopy.y * GameEngine::GameEngine::getDeltaTime()) / 100.;
                        giverPositionCopy.x += (giverVelocityCopy.x * GameEngine::GameEngine::getDeltaTime()) / 100.;
                        giverPositionCopy.y += (giverVelocityCopy.y * GameEngine::GameEngine::getDeltaTime()) / 100.;
                        if (collidesWith(*receiverHitbox, receiverPositionCopy, *giverHitbox, giverPositionCopy)) {
                            addToCollisionComponent(registry, collisions.at(receiverId), receiverId, giverId);
                            break;
                        } else {
                            removeFromCollisionComponent(registry, collisions.at(receiverId), receiverId, giverId);
                        }
                    }
                //}
            }
        }
    }

} // namespace ECS::Systems
