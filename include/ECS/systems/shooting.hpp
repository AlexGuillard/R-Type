/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** controller
*/

#pragma once

#include "ECS/containers/Registry.hpp"
#include "ECS/components/MissileComponent.hpp"
#include "ECS/components/WaveBeamComponent.hpp"

namespace ECS::systems {
	/**
	 * @brief Handles the input of the player
	 */
	void shooting(
		containers::Registry &registry,
		containers::SparseArray<components::MissileComponent> &missileRequests,
		containers::SparseArray<components::WaveBeamComponent> &waveBeamRequests);
}; // namespace ECS::systems
