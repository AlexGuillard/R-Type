/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** controller
*/

#pragma once

#include "ECS/containers/Registry.hpp"
#include "ECS/components/PositionComponent.hpp"
#include "ECS/components/VelocityComponent.hpp"
#include "ECS/components/ControllableComponent.hpp"

namespace ECS::systems {
	// time (in s) player need to hold the fire button to shoot a wave beam
	const double timeNeededForWaveBeam = 1;
	/**
	 * @brief Handles the input of the player
	 */
	void controller(
		containers::Registry &registry,
		ECS::containers::SparseArray<ECS::components::PositionComponent> &positions,
		containers::SparseArray<components::VelocityComponent> &velocities,
		containers::SparseArray<components::ControllableComponent> &controllables);
}; // namespace ECS::systems
