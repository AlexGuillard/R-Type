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
	/**
	 * @brief Handles the input of the player
	 */
	void controller(
		containers::Registry &registry,
		containers::SparseArray<components::VelocityComponent> &velocities,
		containers::SparseArray<components::ControllableComponent> &controllables);
}; // namespace ECS::systems
