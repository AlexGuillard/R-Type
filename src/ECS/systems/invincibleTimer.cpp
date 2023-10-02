/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** invincibleTimer
*/

#include <raylib.h>
#include "ECS/systems/invincibleTimer.hpp"
#include "ECS/Components/InvincibleTimerComponent.hpp"
#include "ECS/Containers/zipper/Zipper.hpp"

namespace ECS::Systems {

    void invincibleTimer(
        [[maybe_unused]] Containers::Registry &registry,
        Containers::SparseArray<Components::InvincibleTimerComponent> &invincibleTimer)
    {
        for (auto &&[invincibleTimer] : ECS::Containers::Zipper(invincibleTimer)) {
            auto &timer = invincibleTimer->timer;
            timer -= GetFrameTime();
        }
    }

}; // namespace ECS::systems
