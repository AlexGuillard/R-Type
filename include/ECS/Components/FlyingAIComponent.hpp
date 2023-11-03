/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** FlyingAIComponent
*/

#pragma once

#include <utility>

namespace ECS::Components {
    struct FlyingAIComponent
    {
        std::pair<float, float> preferedXDistance;
        std::pair<float, float> preferedYDistance;
        float speed;
    };
} // namespace ECS::Components
