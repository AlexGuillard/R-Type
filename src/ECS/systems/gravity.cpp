/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** gravity
*/

#include <raylib.h>
#include "ECS/systems/gravity.hpp"
#include "ECS/components/GravityComponent.hpp"
#include "ECS/components/VelocityComponent.hpp"
#include "ECS/containers/zipper/Zipper.hpp"

namespace ECS::systems {

	void gravity(
		[[maybe_unused]] containers::Registry &registry,
		ECS::containers::SparseArray<ECS::components::VelocityComponent> &velocities,containers::SparseArray<components::GravityComponent> &gravity)
	{
		for (auto &&[velocity, gravity] : ECS::containers::Zipper(velocities, gravity)) {
			velocity->x += gravity->gravity;
			velocity->y += gravity->gravity;
		}
	}

}; // namespace ECS::systems
