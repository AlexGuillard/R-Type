/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** movement
*/

#include <raylib.h>

#include "ECS/systems/movement.hpp"
#include "ECS/components/PositionComponent.hpp"
#include "ECS/components/VelocityComponent.hpp"

namespace ECS::systems {

	void movement(
		[[maybe_unused]] containers::Registry &registry,
		containers::SparseArray<components::PositionComponent> &positions,
		containers::SparseArray<components::VelocityComponent> &velocities)
	{
		for (std::size_t entityId = 0; entityId < registry.size(); entityId++) {
			if (!positions.at(entityId).has_value() || !velocities.at(entityId).has_value())
				continue;
			auto &x = positions.at(entityId)->x;
			auto &y = positions.at(entityId)->y;
			auto &vx = velocities.at(entityId)->x;
			auto &vy = velocities.at(entityId)->y;
			x += vx * GetFrameTime();
			y += vy * GetFrameTime();
		}
	}

}; // namespace ECS::systems
