/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** invincibleTimer
*/

#pragma once

#include "ECS/containers/Registry.hpp"
#include "ECS/components/InvincibleTimerComponent.hpp"

namespace ECS::systems {
	/**
	 * @brief Updates the timer for invincibility
	 */
	void invincibleTimer(
		containers::Registry &registry,
		containers::SparseArray<components::InvincibleTimerComponent> &invincibleTimer);
};
