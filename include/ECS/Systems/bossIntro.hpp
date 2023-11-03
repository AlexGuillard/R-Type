/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** BossIntro
*/

#pragma once

#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/HitBoxComponent.hpp"
#include "ECS/Components/BossIntroComponent.hpp"

namespace ECS::Systems {
    void bossIntro(
        Containers::Registry &registry,
        Containers::SparseArray<Components::PositionComponent> &positions,
        Containers::SparseArray<Components::HitBoxComponent> &hitBoxes,
        Containers::SparseArray<Components::BossIntroComponent> &bossIntros);
} // namespace ECS::Systems
