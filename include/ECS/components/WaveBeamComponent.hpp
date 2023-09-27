/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** WaveBeamComponent
*/

#pragma once

#include <cstddef>

namespace ECS::components {
	/**
	 * @brief Component for entities that request to spawn a wave beam
	 * @param x Position on the x axis
	 * @param y Position on the y axis
	 */
	struct WaveBeamComponent {
		float x;
		float y;
		std::size_t damage = 2;
	};
}; // namespace ECS::components
