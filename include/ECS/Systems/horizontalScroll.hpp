/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** horizontalScroll
*/

#pragma once // NOLINT

#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/HorizontalScrollComponent.hpp"
#include "ECS/Components/PositionComponent.hpp"

namespace ECS::Systems {
    /**
     * @brief Add horizontal scroll to position
     */
    void horizontalScroll(
        Containers::Registry &registry,
        ECS::Containers::SparseArray<ECS::Components::HorizontalScrollComponent> &horizontalScrolls,
        ECS::Containers::SparseArray<ECS::Components::PositionComponent> &positions);
} // namespace ECS::Systems
