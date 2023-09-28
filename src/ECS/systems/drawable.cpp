/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** drawable
*/

#include <unordered_map>

#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/DrawableComponent.hpp"
#include "ECS/Containers/Registry.hpp"
#include "ECS/Containers/zipper/Zipper.hpp"
#include "ECS/Systems/drawable.hpp"
#include "ECS/Systems/Helper/SpriteSheetDrawer.hpp"

namespace ECS::Systems {
    static std::unordered_map<std::string, Texture2D> textures;

    static Texture2D loadTexture(const std::string &path)
    {
        if (!textures.contains(path)) {
            textures[path] = LoadTexture(path.c_str());
        }
        return textures[path];
    }

    void drawable(
        [[maybe_unused]] Containers::Registry &registry,
        Containers::SparseArray<Components::PositionComponent> &positions,
        Containers::SparseArray<Components::DrawableComponent> &drawables
    )
    {
        for (auto &&[position, drawable] : Containers::Zipper(positions, drawables)) {
            Helper::SpriteSheetDrawer drawer(
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

}; // namespace ECS::Systems
