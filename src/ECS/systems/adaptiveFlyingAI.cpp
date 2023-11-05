/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** FlyingAI
*/

#include "ECS/Systems/adaptiveFlyingAI.hpp"
#include "ECS/Containers/zipper/Zipper.hpp"

namespace ECS::Systems {
    template <typename T>
    static T abs(T value)
    {
        return value < 0 ? -value : value;
    }

    void adaptiveFlyingAI(
        Containers::Registry &registry,
        Containers::SparseArray<Components::AdaptiveFlyingAIComponent> &AIs,
        Containers::SparseArray<Components::FlyingAIComponent> &flyingAIs,
        Containers::SparseArray<Components::TargetComponent> &targets)
    {
        for (auto &&[ai, flyingAI, target] : Containers::Zipper(AIs, flyingAIs, targets)) {
            if (target->targetId == ECS::NullEntity()) { continue; }
            if (abs(target->distance) <= ai->speedPerDistance[0].first) {
                flyingAI->speed = ai->speedPerDistance[0].second;
            } else if (abs(target->distance) <= ai->speedPerDistance[1].first) {
                flyingAI->speed = ai->speedPerDistance[1].second;
            } else {
                flyingAI->speed = ai->speedPerDistance[2].second;
            }
        }
    }
} // namespace ECS::Systems
