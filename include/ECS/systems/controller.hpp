/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** controller
*/

#pragma once

#include "ECS/containers/Registry.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Components/ControllableComponent.hpp"

namespace ECS::systems {
	// time (in s) player need to hold the fire button to shoot a wave beam
	const double timeNeededForWaveBeam = 1;
	/**
	 * @brief Handles the input of the player
	 */
	void controller(
		containers::Registry &registry,
		ECS::containers::SparseArray<ECS::Components::PositionComponent> &positions,
		containers::SparseArray<Components::VelocityComponent> &velocities,
		containers::SparseArray<Components::ControllableComponent> &controllables);
}; // namespace ECS::systems
