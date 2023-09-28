/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** drawable
*/

#pragma once

namespace ECS::Systems {
	/**
	 * @brief Draws the entities with a position and a drawable component
	 */
	void drawable(
		Containers::Registry &registry,
		Containers::SparseArray<Components::PositionComponent> &positions,
		Containers::SparseArray<Components::DrawableComponent> &drawables);

}; // namespace ECS::Systems
