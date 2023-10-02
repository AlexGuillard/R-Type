/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** PositionComponent
*/

#pragma once

namespace ECS::Components {
	/**
	 * @brief Component that contains the position of an entity
	 * @param x Position on the x axis
	 * @param y Position on the y axis
	 */
	struct PositionComponent {
		float x;
		float y;
	};
}; // namespace ECS::Components
