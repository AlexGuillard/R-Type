/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** DamageComponent
*/

#pragma once

#include <cstddef>

namespace ECS::Components {
    /**
     * @brief Component for entities that deal damage
     * @param damage Damage of the entity
     */
    struct DamageComponent {
        std::size_t damage = 1;
    };
}; // namespace ECS::Components
