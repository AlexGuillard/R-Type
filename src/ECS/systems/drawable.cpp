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
#include "ECS/Containers/zipper/IndexedZipper.hpp"
#include "ECS/Systems/drawable.hpp"
#include "ECS/Systems/Helper/SpriteSheetDrawer.hpp"
#include "Assets/AssetLoader.hpp"
#include "client/display/Display.hpp"

#ifdef DEBUG
#include "ECS/Components/CollisionComponent.hpp"
#include "ECS/Components/HitBoxComponent.hpp"
#endif
namespace ECS::Systems {
#ifdef DEBUG
    /**
     * @brief Draws the hitbox of an entity.
     * If the entity is colliding with another entity, the hitbox is drawn in red.
     * @param registry
     * @param entity
     * @param position
     * @param hitboxes
     * @param collisions
     */
    static void debugDraw(
        Entity const &entity,
        const Components::PositionComponent &position,
        const std::optional<Components::HitBoxComponent> &hitbox,
        const std::optional<Components::CollisionComponent> &collision
    )
    {
        if (hitbox.has_value()) { // Draw hitbox
            DrawRectangleLines(
                position.x,
                position.y,
                hitbox->width,
                hitbox->height,
                BLUE
            );
        }
        if (collision.has_value() && hitbox.has_value()) { // Draw collision
            DrawRectangleLines(
                position.x,
                position.y,
                hitbox->width,
                hitbox->height,
                RED
            );
        }
    }
#endif

    void drawable(
        [[maybe_unused]] Containers::Registry &registry,
        Containers::SparseArray<Components::PositionComponent> &positions,
        Containers::SparseArray<Components::DrawableComponent> &drawables
    )
    {
    #ifdef DEBUG
        auto &collisions = registry.getComponents<Components::CollisionComponent>();
        auto &hitboxes = registry.getComponents<Components::HitBoxComponent>();
    #endif
        Screen::Display::beginDrawCamera();
        for (auto &&[eId, position, drawable] : Containers::IndexedZipper(positions, drawables)) {
            Helper::SpriteSheetDrawer drawer(
                Assets::AssetLoader::loadTexturePng(drawable->spriteSheetIndex),
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
            drawer.draw(Utils::Vector2(position->x, position->y));
        }
    #ifdef DEBUG
        for (auto &&[eId, position, hitbox] : Containers::IndexedZipper(positions, hitboxes)) {
            debugDraw(
                registry.entityFromIndex(eId),
                *position,
                *hitbox,
                collisions.at(eId)
            );
        }
    #endif
        Screen::Display::endDrawCamera();
    }

}; // namespace ECS::Systems
