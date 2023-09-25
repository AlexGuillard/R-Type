/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** controller
*/

#include <raylib.h>

#include "ECS/systems/controller.hpp"
#include "ECS/components/VelocityComponent.hpp"
#include "ECS/components/ControllableComponent.hpp"
#include "ECS/containers/zipper/Zipper.hpp"

namespace ECS::systems {

	template <typename T>
	static T clamp(T value, T min, T max)
	{
		if (value < min)
			return min;
		if (value > max)
			return max;
		return value;
	}

	template <typename T>
	static T abs(T value)
	{
		return value < 0 ? -value : value;
	}

	void controller(
		[[maybe_unused]] ECS::containers::Registry &registry,
		ECS::containers::SparseArray<ECS::components::VelocityComponent> &velocities,
		ECS::containers::SparseArray<ECS::components::ControllableComponent> &controllables)
	{
		const float MAX_SPEED = 500;
		const float NB_FRAME_TO_MAX_SPEED = 5;
		const float NB_FRAME_TO_STOP = 5;
		const float ACCELERATION = MAX_SPEED / NB_FRAME_TO_MAX_SPEED;
		const float DECELERATION = MAX_SPEED / NB_FRAME_TO_STOP;

		for (auto &&[velocity, controllable] : ECS::containers::Zipper(velocities, controllables)) {
			if (IsKeyDown(controllable->up))
				velocity->y -= 1 * ACCELERATION;
			else if (IsKeyDown(controllable->down))
				velocity->y += 1 * ACCELERATION;
			else {
				if (abs(velocity->y) < DECELERATION)
					velocity->y = 0;
				else
					velocity->y += (velocity->y > 0 ? -1 : 1) * DECELERATION;
			}
			if (IsKeyDown(controllable->left))
				velocity->x -= 1 * ACCELERATION;
			else if (IsKeyDown(controllable->right))
				velocity->x += 1 * ACCELERATION;
			else {
				if (abs(velocity->x) < DECELERATION)
					velocity->x = 0;
				else
					velocity->x += (velocity->x > 0 ? -1 : 1) * DECELERATION;
			}
			velocity->x = clamp(velocity->x, -MAX_SPEED, MAX_SPEED);
			velocity->y = clamp(velocity->y, -MAX_SPEED, MAX_SPEED);
		}
	}

}; // namespace ECS::systems
