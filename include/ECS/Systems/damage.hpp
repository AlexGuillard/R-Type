/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** damage
*/

#pragma once

#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/CollisionComponent.hpp"
#include "ECS/Components/DamageComponent.hpp"
#include "ECS/Components/TeamComponent.hpp"
#include "ECS/Components/HPComponent.hpp"

namespace ECS::Systems {

    /**
     * @brief
     *
     * @param registry
     * @param damage
     * @param team
     * @param hpComponents
     * @param collision
     */
    void damage(
        Containers::Registry &registry,
        Containers::SparseArray<Components::CollisionComponent> &collision,
        Containers::SparseArray<Components::DamageComponent> &damage,
        Containers::SparseArray<Components::TeamComponent> &team,
        Containers::SparseArray<Components::HPComponent> &hpComponents
    );

} // namespace ECS::Systems
