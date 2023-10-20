/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** ControllableComponent
*/

#pragma once

#include <cstddef>

#include "enums.hpp"

namespace ECS::Components {
    /**
     * @brief Component that contains the data needed to control an entity
     * @param up Key to go up
     * @param down Key to go down
     * @param left Key to go left
     * @param right Key to go right
     * @param fire Key to fire
     * @param force Key to use force
     * @param timeFireButtonHeld Time (in sec) since the fire button is held
     */
    struct ControllableComponent {
        Enums::KeyboardKey up = Enums::KeyboardKey::KEY_UP;
        Enums::KeyboardKey down = Enums::KeyboardKey::KEY_DOWN;
        Enums::KeyboardKey left = Enums::KeyboardKey::KEY_LEFT;
        Enums::KeyboardKey right = Enums::KeyboardKey::KEY_RIGHT;
        Enums::KeyboardKey fire = Enums::KeyboardKey::KEY_SPACE;
        Enums::KeyboardKey force = Enums::KeyboardKey::KEY_LEFT_SHIFT;
        double timeFireButtonHeld = 0.0;
    };
} // namespace ECS::Components
