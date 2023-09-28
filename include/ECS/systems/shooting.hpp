/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** controller
*/

#pragma once

#include "ECS/containers/Registry.hpp"
#include "ECS/Components/MissileComponent.hpp"
#include "ECS/Components/WaveBeamComponent.hpp"

namespace ECS::systems {
	/**
	 * @brief Handles the input of the player
	 */
	void shooting(
		containers::Registry &registry,
		containers::SparseArray<Components::MissileComponent> &missileRequests,
		containers::SparseArray<Components::WaveBeamComponent> &waveBeamRequests);
}; // namespace ECS::systems
