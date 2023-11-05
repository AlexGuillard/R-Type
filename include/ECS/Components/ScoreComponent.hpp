/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ScoreComponent.hpp
*/

#pragma once

#include <cstddef>

namespace ECS::Components {
    /**
     * @brief component to indicate score given by mob
     *
     */
    struct ScoreComponent {
        int score;
    };
} // namespace ECS::Components
