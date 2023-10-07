/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** solid
*/

#include <cstdint>
#include <cmath>

#include "ECS/Systems/solid.hpp"
#include "ECS/Containers/zipper/IndexedZipper.hpp"

namespace ECS::Systems {

    void solid(
        Containers::Registry &registry,
        Containers::SparseArray<Components::SolidComponent> &solids,
        Containers::SparseArray<Components::HitBoxComponent> &hitBoxes,
        Containers::SparseArray<Components::CollisionComponent> &allCollisions,
        Containers::SparseArray<Components::PositionComponent> &positions)
    {
        for (auto &&[idx, solid, hitBox, collisions, position]
            : Containers::IndexedZipper(solids, hitBoxes, allCollisions, positions)) {
            for (auto &&entity : collisions->collisions) {
                auto &entityHitBox = hitBoxes.at(entity);
                auto &entityPosition = positions.at(entity);
                int overlapLeft = (entityPosition->x + entityHitBox->width) - position->x;
                int overlapRight = (position->x + hitBox->width) - entityPosition->x;
                int overlapTop = (entityPosition->y + entityHitBox->height) - position->y;
                int overlapBottom = (position->y + hitBox->height) - entityPosition->y;

                if (overlapLeft > 0 && overlapLeft < overlapBottom && overlapLeft < overlapTop && overlapLeft < overlapRight) {
                    entityPosition->x = position->x - entityHitBox->width;
                } else if (overlapRight > 0 && overlapRight < overlapBottom && overlapRight < overlapTop && overlapRight < overlapLeft) {
                    entityPosition->x = position->x + hitBox->width;
                } else if (overlapTop > 0 && overlapTop < overlapLeft && overlapTop < overlapRight && overlapTop < overlapBottom) {
                    entityPosition->y = position->y - entityHitBox->height;
                } else if (overlapBottom > 0 && overlapBottom < overlapLeft && overlapBottom < overlapRight && overlapBottom < overlapTop) {
                    entityPosition->y = position->y + hitBox->height;
                }
            }
        }
    }
} // namespace ECS::Systems
