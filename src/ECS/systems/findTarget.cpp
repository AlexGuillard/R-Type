/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** findTarget
*/

#include "ECS/Systems/findTarget.hpp"
#include "ECS/Containers/zipper/IndexedZipper.hpp"

void ECS::Systems::findTarget(
    Containers::Registry &registry,
    ECS::Containers::SparseArray<ECS::Components::TargetComponent> &targets,
    ECS::Containers::SparseArray<ECS::Components::HPComponent> &hpComponents,
    ECS::Containers::SparseArray<ECS::Components::InvincibleTimerComponent> &invincibleTimers,
    ECS::Containers::SparseArray<ECS::Components::TeamComponent> &teams)
{
    for (auto &&[eId, target] : Containers::IndexedZipper(targets)) {
        if (target->targetId != ECS::NullEntity()) { continue; }
        for (auto &&[possibleTarget, hp] : Containers::IndexedZipper(hpComponents)) {
            if (invincibleTimers[possibleTarget]) { continue; }
            if (!teams[possibleTarget]) {
                target->targetId = possibleTarget;
                break;
            } else if (teams[eId]->team != teams[possibleTarget]->team) {
                target->targetId = possibleTarget;
                break;
            }
        }
    }
}
