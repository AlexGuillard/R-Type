/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** drawable
*/

#include "ECS/components/PositionComponent.hpp"
#include "ECS/components/DrawableComponent.hpp"
#include "ECS/containers/Registry.hpp"
#include "ECS/systems/drawable.hpp"
#include "ECS/systems/helper/SpriteSheetDrawer.hpp"

namespace ECS::systems {

	void drawable(
		[[maybe_unused]] containers::Registry &registry,
		containers::SparseArray<components::PositionComponent> &positions,
		containers::SparseArray<components::DrawableComponent> &drawables
	)
	{
		for (std::size_t entityId = 0; entityId < registry.size(); entityId++) {
			if (!positions.at(entityId).has_value() || !drawables.at(entityId).has_value())
				continue;
			auto &position = positions.at(entityId);
			auto &drawable = drawables.at(entityId);
			helper::SpriteSheetDrawer drawer(
				drawable->texture,
				drawable->frameRatio,
				drawable->start,
				drawable->end,
				drawable->boomerang,
				drawable->frame,
				drawable->forward
			);
			const double time = GetTime();
			const float frameDuration = 1.0 / drawable->fps;
			if ((time - drawable->timeAtLastFrameChange) > frameDuration) {
				drawable->frame = drawer.next();
				drawable->forward = drawer.isForward();
				drawable->timeAtLastFrameChange = time;
			}
			drawer.draw(Vector2(position->x, position->y));
		}
	}

}; // namespace ECS::systems
