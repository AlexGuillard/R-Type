/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** movement
*/

#pragma once

#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"

namespace ECS::Systems {
	/** @brief Updates the position of the entities using their velocity */
	void movement(
		Containers::Registry &registry,
		Containers::SparseArray<Components::PositionComponent> &positions,
		Containers::SparseArray<Components::VelocityComponent> &velocities);
};
