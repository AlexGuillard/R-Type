/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** gravity
*/

#pragma once

#include "ECS/containers/Registry.hpp"
#include "ECS/components/GravityComponent.hpp"

namespace ECS::systems {
	/** 
	 * @brief Add gravity to velocity
	 */
	void gravity(
		containers::Registry &registry,
		containers::SparseArray<components::GravityComponent> &gravity);
};
