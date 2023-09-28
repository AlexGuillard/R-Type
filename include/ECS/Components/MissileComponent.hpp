/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** MissileComponent
*/

#pragma once

#include <cstddef>

namespace ECS::Components {
	// X velocity in pixels per second for the missile that will be spawned
	static const float missileSpeed = 500;
	static const std::size_t missileBaseDamage = 1;
	/**
	 * @brief Component for entities that request to spawn a missile
	 * @param x Position on the x axis
	 * @param y Position on the y axis
	 * @param damage Damage of the missile
	 */
	struct MissileComponent {
		float x;
		float y;
		std::size_t damage = missileBaseDamage;
	};
}; // namespace ECS::Components
