/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** movement
*/

#include <raylib.h>

#include "ECS/Systems/movement.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"

namespace ECS::Systems {

	void movement(
		[[maybe_unused]] Containers::Registry &registry,
		Containers::SparseArray<Components::PositionComponent> &positions,
		Containers::SparseArray<Components::VelocityComponent> &velocities)
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

}; // namespace ECS::Systems
