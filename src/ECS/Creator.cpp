/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Creator
*/

#include <cstdint>
#include "ECS/Creator.hpp"
#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/WalkingAIComponent.hpp"
#include "ECS/Components/TargetComponent.hpp"
#include "ECS/Components/GravityComponent.hpp"
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
#include "enums.hpp"

namespace ECS {

    Entity Creator::addWalkingAI(
        const Entity &entity,
        Containers::Registry &registry,
        const Entity &target,
        std::pair<float, float> preferredDistance,
        float speed,
        bool dropsDownLedge,
        bool jumpsOverObstacle)
    {
        registry.emplaceComponent<Components::WalkingAIComponent>(entity, std::make_pair(100.F, 200.F), 100);
        registry.emplaceComponent<Components::TargetComponent>(entity, static_cast<std::size_t>(target));
        registry.emplaceComponent<Components::GravityComponent>(entity, 9.81F);
        registry.emplaceComponent<Components::CollidableComponent>(entity);
        return entity;
    }

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
        const uint8_t nbFrameInAnimation = 8;

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

    void Creator::createAlly(Containers::Registry &registry, size_t id, int x, int y, Enums::PlayerColor color)
    {
        const Vector2 nbFrameInSpriteSheet = Vector2(5, 5);
        const uint8_t nbFrameInAnimation = 5;

        ECS::Entity ally = ECS::Creator::createCharacter(registry, 1, 1, 33, 14, id);
        registry.getComponents<Components::PositionComponent>().at(ally)->x = x;
        registry.getComponents<Components::PositionComponent>().at(ally)->y = y;
        Components::DrawableComponent drawableComponent = {
            Assets::AssetsIndex::R_TYPESHEET42_PNG,
            nbFrameInSpriteSheet, // frameRatio
            Vector2(nbFrameInAnimation * (int)color, 0), // start
            Vector2(nbFrameInAnimation + (nbFrameInAnimation * (int)color), 0), // end
            true, // boomerang
            nbFrameInAnimation // fps
        };
        registry.addComponent<Components::DrawableComponent>(ally, std::move(drawableComponent));
    }

}; // namespace ECS
