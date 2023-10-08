/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** TargetComponent
*/

#pragma once

#include <cstdint>

namespace ECS::Components {
    /**
     * @brief
     * @param targetId Id of the entity being targeted
     * @param t Time (in sec.) since the targeting started
     * @param dX Difference between this x pos and the target x pos
     * @param dY Difference between this y pos and the target y pos
     * @param distance Euclidean distance to the target
     */
    struct TargetComponent
    {
        std::size_t targetId;
        float t = 0;
        float dX = 0;
        float dY = 0;
        float distance = 0;
    };

} // namespace ECS::Components
