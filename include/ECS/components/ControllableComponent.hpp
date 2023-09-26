/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** ControllableComponent
*/

#pragma once

#include <raylib.h>
#include <cstddef>

namespace ECS::components {
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
		KeyboardKey up = KEY_UP;
		KeyboardKey down = KEY_DOWN;
		KeyboardKey left = KEY_LEFT;
		KeyboardKey right = KEY_RIGHT;
		KeyboardKey fire = KEY_SPACE;
		KeyboardKey force = KEY_LEFT_SHIFT;
		double timeFireButtonHeld = 0.0;
	};
} // namespace ECS::components
