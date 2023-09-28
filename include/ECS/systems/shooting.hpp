/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** controller
*/

#pragma once

#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/MissileComponent.hpp"
#include "ECS/Components/WaveBeamComponent.hpp"

namespace ECS::systems {
	/**
	 * @brief Handles the input of the player
	 */
	void shooting(
		Containers::Registry &registry,
		Containers::SparseArray<Components::MissileComponent> &missileRequests,
		Containers::SparseArray<Components::WaveBeamComponent> &waveBeamRequests);
}; // namespace ECS::systems
