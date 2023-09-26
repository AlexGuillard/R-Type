/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** drawable
*/

#include <unordered_map>

#include "ECS/components/PositionComponent.hpp"
#include "ECS/components/DrawableComponent.hpp"
#include "ECS/containers/Registry.hpp"
#include "ECS/containers/zipper/Zipper.hpp"
#include "ECS/systems/drawable.hpp"
#include "ECS/systems/helper/SpriteSheetDrawer.hpp"

namespace ECS::systems {
	std::unordered_map<std::string, Texture2D> textures;

	static Texture2D loadTexture(const std::string &path)
	{
		if (textures.find(path) == textures.end()) {
			textures[path] = LoadTexture(path.c_str());
		}
		return textures[path];
	}

	void drawable(
		[[maybe_unused]] containers::Registry &registry,
		containers::SparseArray<components::PositionComponent> &positions,
		containers::SparseArray<components::DrawableComponent> &drawables
	)
	{
		for (auto &&[position, drawable] : containers::Zipper(positions, drawables)) {
			helper::SpriteSheetDrawer drawer(
				loadTexture(drawable->texture),
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
