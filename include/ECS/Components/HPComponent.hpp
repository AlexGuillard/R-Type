/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** HPComponent
*/

#pragma once

#include <cstddef>

namespace ECS::Components {
	/**
	 * @brief Component for entities that have HP
	 * @param hp HP of the entity
	 */
	struct HPComponent {
		std::size_t hp = 1;
	};
}; // namespace ECS::Components
