/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** invincibleTimer
*/

#pragma once

#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/InvincibleTimerComponent.hpp"

namespace ECS::Systems {
    /**
     * @brief Updates the timer for invincibility
     */
    void invincibleTimer(
        Containers::Registry &registry,
        Containers::SparseArray<Components::InvincibleTimerComponent> &invincibleTimer);
};
