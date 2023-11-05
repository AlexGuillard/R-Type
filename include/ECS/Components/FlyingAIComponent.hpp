/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** FlyingAIComponent
*/

#pragma once

#include <utility>

namespace ECS::Components {
    /**
     * @brief Component for entities that can fly towards a target
     * @param preferedXDistance the prefered distance on the x axis
     * @param preferedYDistance the prefered distance on the y axis
     * @param speed the speed of the entity
    */
    struct FlyingAIComponent
    {
        std::pair<float, float> preferedXDistance;
        std::pair<float, float> preferedYDistance;
        float speed;
    };
} // namespace ECS::Components
