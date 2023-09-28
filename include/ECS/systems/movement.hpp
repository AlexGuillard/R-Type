/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** movement
*/

#pragma once

#include "ECS/containers/Registry.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"

namespace ECS::systems {
	/** @brief Updates the position of the entities using their velocity */
	void movement(
		containers::Registry &registry,
		containers::SparseArray<Components::PositionComponent> &positions,
		containers::SparseArray<Components::VelocityComponent> &velocities);
};
