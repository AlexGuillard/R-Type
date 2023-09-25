/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** ControllableComponent
*/

#pragma once

#include <raylib.h>

namespace ECS::components {
	/**
	 * @brief Component that contains the data needed to control an entity
	 * @param up Key to go up
	 * @param down Key to go down
	 * @param left Key to go left
	 * @param right Key to go right
	 */
	struct ControllableComponent {
		KeyboardKey up = KEY_UP;
		KeyboardKey down = KEY_DOWN;
		KeyboardKey left = KEY_LEFT;
		KeyboardKey right = KEY_RIGHT;
		KeyboardKey fire = KEY_SPACE;
		KeyboardKey force = KEY_LEFT_SHIFT;
	};
} // namespace ECS::components
