/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Creator
*/

#include "ECS/Creator.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Components/DamageComponent.hpp"
#include "ECS/Components/HPComponent.hpp"
#include "ECS/Components/HitBoxComponent.hpp"
#include "ECS/Components/DrawableComponent.hpp"
#include "ECS/Components/ControllableComponent.hpp"
#include "ECS/Components/MissileComponent.hpp"
#include "ECS/Components/WaveBeamComponent.hpp"
#include "ECS/Components/CollidableComponent.hpp"
#include "ECS/Components/CollisionComponent.hpp"
#include "ECS/Components/SinMovementComponent.hpp"
#include "Assets/generatedAssets.hpp"

namespace ECS {

    Entity Creator::createCharacter(
        Containers::Registry &registry,
        /* enum TeamGroup team, */
        std::size_t damage,
        std::size_t health,
        std::size_t width,
        std::size_t height
    )
    {
        Entity entity = registry.spawnEntity();

        registry.emplaceComponent<Components::PositionComponent>(entity, 0, 0);
        registry.emplaceComponent<Components::VelocityComponent>(entity, 0, 0);
        registry.emplaceComponent<Components::DamageComponent>(entity, damage);
        registry.emplaceComponent<Components::HPComponent>(entity, health);
        registry.emplaceComponent<Components::HitBoxComponent>(entity, width, height);
        return entity;
    }

    Entity Creator::createCharacter(
        Containers::Registry &registry,
        /* enum TeamGroup team, */
        std::size_t damage,
        std::size_t health,
        std::size_t width,
        std::size_t height,
        std::size_t id
    )
    {
        Entity entity = registry.entityFromIndex(id);

        registry.emplaceComponent<Components::PositionComponent>(entity, 0, 0);
        registry.emplaceComponent<Components::VelocityComponent>(entity, 0, 0);
        registry.emplaceComponent<Components::DamageComponent>(entity, damage);
        registry.emplaceComponent<Components::HPComponent>(entity, health);
        registry.emplaceComponent<Components::HitBoxComponent>(entity, width, height);
        return entity;
    }

    void Creator::createEnemyBasic(Containers::Registry &registry, size_t id, int x, int y)
    {
        const Vector2 nbFrameInSpriteSheet = Vector2(16, 1);
        const u_char nbFrameInAnimation = 8;

        ECS::Entity enemyBasic = ECS::Creator::createCharacter(registry, 1, 1, 20, 24, id);
        registry.emplaceComponent<Components::SinMovementComponent>(enemyBasic);
        registry.getComponents<Components::SinMovementComponent>().at(enemyBasic)->horizontalOffset = x;
        registry.getComponents<Components::SinMovementComponent>().at(enemyBasic)->verticalOffset = y;
        registry.getComponents<Components::SinMovementComponent>().at(enemyBasic)->frequency = 0.01;
        Components::DrawableComponent drawableComponent = {
            Assets::AssetsIndex::R_TYPESHEET5_PNG,
            nbFrameInSpriteSheet, // frameRatio
            Vector2(0, 0), // start
            Vector2(nbFrameInAnimation, 0), // end
            true, // boomerang
            nbFrameInAnimation // fps
        };
        registry.addComponent<Components::DrawableComponent>(enemyBasic, std::move(drawableComponent));
    }

}; // namespace ECS
