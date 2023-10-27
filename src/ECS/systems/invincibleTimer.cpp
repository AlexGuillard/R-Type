/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** invincibleTimer
*/

#include "GameEngine/GameEngine.hpp"
#include "ECS/Systems/invincibleTimer.hpp"
#include "ECS/Components/InvincibleTimerComponent.hpp"
#include "ECS/Containers/zipper/Zipper.hpp"

namespace ECS::Systems {

    void invincibleTimer(
        [[maybe_unused]] Containers::Registry &registry,
        Containers::SparseArray<Components::InvincibleTimerComponent> &invincibleTimer)
    {
        for (auto &&[invincibleTimer] : ECS::Containers::Zipper(invincibleTimer)) {
            auto &timer = invincibleTimer->timer;
            timer -= GameEngine::GameEngine::getDeltaTime();
        }
    }

}; // namespace ECS::systems
