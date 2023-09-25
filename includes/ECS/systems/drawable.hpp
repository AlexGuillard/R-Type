/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** drawable
*/

#pragma once

namespace ECS::systems {
	/**
	 * @brief Draws the entities with a position and a drawable component
	 */
	void drawable(
		containers::Registry &registry,
		containers::SparseArray<components::PositionComponent> &positions,
		containers::SparseArray<components::DrawableComponent> &drawables);

}; // namespace ECS::systems
