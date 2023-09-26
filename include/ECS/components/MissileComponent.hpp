/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** MissileComponent
*/

#pragma once

#include <cstddef>

namespace ECS::components {
	static const float missileSpeed = 500;
	/**
	 * @brief Component for entities that request to spawn a missile
	 * @param x Position on the x axis
	 * @param y Position on the y axis
	 * @param damage Damage of the missile
	 */
	struct MissileComponent {
		float x;
		float y;
		std::size_t damage = 1;
	};
}; // namespace ECS::components
