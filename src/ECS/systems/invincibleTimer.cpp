/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** invincibleTimer
*/

#include <raylib.h>
#include "ECS/systems/invincibleTimer.hpp"
#include "ECS/components/InvincibleTimerComponent.hpp"
#include "ECS/containers/zipper/Zipper.hpp"

namespace ECS::systems {

	void invincibleTimer(
		[[maybe_unused]] containers::Registry &registry,
		containers::SparseArray<components::InvincibleTimerComponent> &invincibleTimer)
	{
		for (auto &&[invincibleTimer] : ECS::containers::Zipper(invincibleTimer)) {
			auto &timer = invincibleTimer->timer;
			timer -= GetFrameTime();
		}
	}

}; // namespace ECS::systems
