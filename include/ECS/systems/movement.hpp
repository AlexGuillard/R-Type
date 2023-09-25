/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** movement
*/

#pragma once

#include "ECS/containers/Registry.hpp"
#include "ECS/components/PositionComponent.hpp"
#include "ECS/components/VelocityComponent.hpp"

namespace ECS::systems {
	/** @brief Updates the position of the entities using their velocity */
	void movement(
		containers::Registry &registry,
		containers::SparseArray<components::PositionComponent> &positions,
		containers::SparseArray<components::VelocityComponent> &velocities);
};
