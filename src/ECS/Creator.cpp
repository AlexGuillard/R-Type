/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Creator
*/

#include <cstdint>
#include <utility>
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
#include "ECS/Components/HorizontalScrollComponent.hpp"
#include "Assets/generatedAssets.hpp"
#include "enums.hpp"

namespace ECS {

    float Creator::mLevelScrollSpeed = Creator::defaultScrollSpeed;

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

    void Creator::setLevelScrollSpeed(float speed)
    {
        mLevelScrollSpeed = speed;
    }

    float Creator::getLevelScrollSpeed()
    {
        return mLevelScrollSpeed;
    }

    Entity Creator::createCharacter(
        Containers::Registry &registry,
        enum Enums::TeamGroup team,
        std::size_t damage,
        std::size_t health,
        std::size_t width,
        std::size_t height
    )
    {
        Entity entity = registry.spawnEntity();

        return Creator::createCharacter(registry, team, damage, health, width, height, entity);
    }

    Entity Creator::createCharacter(
        Containers::Registry &registry,
        enum Enums::TeamGroup team,
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
        registry.emplaceComponent<Components::TeamComponent>(entity, team);
        registry.emplaceComponent<Components::CollidableComponent>(entity);
        return entity;
    }

    Entity Creator::createGroundedCharacter(
        Containers::Registry &registry,
        enum Enums::TeamGroup team,
        std::size_t damage,
        std::size_t health,
        std::size_t width,
        std::size_t height,
        std::size_t id
    )
    {
        Entity entity = Creator::createCharacter(registry, team, damage, health, width, height, id);

        registry.emplaceComponent<Components::HorizontalScrollComponent>(entity, mLevelScrollSpeed);
        return entity;
    }

    Entity Creator::createMissile(Containers::Registry &registry, size_t id, int x, int y, Enums::TeamGroup team)
    {
        const Utils::Vector2 missileFramePos(2, 0);
        const uint8_t nbFrameInSpriteSheet = 6;

        ECS::Entity enemyBasic = ECS::Creator::createCharacter(registry, team, 1, 1, 16, 16, id);
        registry.getComponents<Components::PositionComponent>().at(enemyBasic)->x = x;
        registry.getComponents<Components::PositionComponent>().at(enemyBasic)->y = y;
        registry.getComponents<Components::VelocityComponent>().at(enemyBasic)->x = Components::missileSpeed;
        registry.getComponents<Components::VelocityComponent>().at(enemyBasic)->y = 0;
        registry.emplaceComponent<Components::DrawableComponent>(enemyBasic,
                Assets::AssetsIndex::MISSILE_PNG,
                Utils::Vector2(nbFrameInSpriteSheet, 1), // frameRatio
                missileFramePos, // start
                missileFramePos // end
        );
        return enemyBasic;
    }

    Entity Creator::createEnemyBasic(Containers::Registry &registry, size_t id, int x, int y)
    {
        const Utils::Vector2 nbFrameInSpriteSheet(16, 1);
        const uint8_t nbFrameInAnimation = 8;

        ECS::Entity enemyBasic = ECS::Creator::createCharacter(registry, Enums::TeamGroup::ENEMY, 1, 1, 20, 24, id);
        registry.emplaceComponent<Components::PositionComponent>(enemyBasic, x, y);
        registry.emplaceComponent<Components::SinMovementComponent>(enemyBasic);
        registry.getComponents<Components::SinMovementComponent>().at(enemyBasic)->horizontalOffset = x;
        registry.getComponents<Components::SinMovementComponent>().at(enemyBasic)->verticalOffset = y;
        registry.emplaceComponent<Components::DrawableComponent>(enemyBasic,
            Assets::AssetsIndex::R_TYPESHEET5_PNG,
            nbFrameInSpriteSheet, // frameRatio
            Utils::Vector2(0, 0), // start
            Utils::Vector2(nbFrameInAnimation, 0), // end
            true, // boomerang
            nbFrameInAnimation // fps
        );
        return enemyBasic;
    }

    Entity Creator::createBink(Containers::Registry &registry, size_t id, int x, int y)
    {
        const Utils::Vector2 nbFrameInSpriteSheet(6, 2);
        const uint8_t nbFrameInAnimation = 3;

        ECS::Entity bink = ECS::Creator::createGroundedCharacter(registry, Enums::TeamGroup::ENEMY, 1, 1, 28, 33, id);
        registry.getComponents<Components::PositionComponent>().at(bink)->x = x;
        registry.getComponents<Components::PositionComponent>().at(bink)->y = y;
        registry.emplaceComponent<Components::DrawableComponent>(bink,
            Assets::AssetsIndex::R_TYPESHEET7_PNG,
            nbFrameInSpriteSheet, // frameRatio
            Utils::Vector2(0, 0), // start
            Utils::Vector2(nbFrameInAnimation, 0), // end
            true, // boomerang
            nbFrameInAnimation // fps
        );
        registry.emplaceComponent<Components::WalkingAIComponent>(bink, std::make_pair(250.F, 500.F), 100);
        registry.emplaceComponent<Components::GravityComponent>(bink, Creator::defaultGravity);
        return bink;
    }

    Entity Creator::createScant(Containers::Registry &registry, size_t id, int x, int y)
    {
        const Utils::Vector2 nbFrameInSpriteSheet(6, 1);
        const uint8_t nbFrameInAnimation = 3;

        ECS::Entity scant = ECS::Creator::createCharacter(registry, Enums::TeamGroup::ENEMY, 1, 1, 58, 54, id);
        registry.getComponents<Components::PositionComponent>().at(scant)->x = x;
        registry.getComponents<Components::PositionComponent>().at(scant)->y = y;
        registry.emplaceComponent<Components::DrawableComponent>(scant,
            Assets::AssetsIndex::R_TYPESHEET9_2_PNG,
            nbFrameInSpriteSheet, // frameRatio
            Utils::Vector2(0, 0), // start
            Utils::Vector2(nbFrameInAnimation, 0), // end
            false, // boomerang
            nbFrameInAnimation // fps
        );
        return scant;
    }

    Entity Creator::createBug(Containers::Registry &registry, size_t id, int x, int y)
    {
        const Utils::Vector2 nbFrameInSpriteSheet(8, 2);
        const uint8_t nbFrameInAnimation = 16;

        ECS::Entity bug = ECS::Creator::createCharacter(registry, Enums::TeamGroup::ENEMY, 1, 1, 30, 23, id);
        registry.getComponents<Components::PositionComponent>().at(bug)->x = x;
        registry.getComponents<Components::PositionComponent>().at(bug)->y = y;
        registry.emplaceComponent<Components::DrawableComponent>(bug,
            Assets::AssetsIndex::R_TYPESHEET8_PNG,
            nbFrameInSpriteSheet, // frameRatio
            Utils::Vector2(0, 0), // start
            Utils::Vector2(nbFrameInAnimation, 0), // end
            false, // boomerang
            nbFrameInAnimation // fps
        );
        return bug;
    }

    Entity Creator::createCancer(Containers::Registry &registry, size_t id, int x, int y)
    {
        const Utils::Vector2 nbFrameInSpriteSheet(6, 1);
        const uint8_t nbFrameInAnimation = 3;

        ECS::Entity cancer = ECS::Creator::createCharacter(registry, Enums::TeamGroup::ENEMY, 1, 1, 32, 32, id);
        registry.getComponents<Components::PositionComponent>().at(cancer)->x = x;
        registry.getComponents<Components::PositionComponent>().at(cancer)->y = y;
        registry.emplaceComponent<Components::DrawableComponent>(cancer,
            Assets::AssetsIndex::R_TYPESHEET11_PNG,
            nbFrameInSpriteSheet, // frameRatio
            Utils::Vector2(0, 0), // start
            Utils::Vector2(nbFrameInAnimation, 0), // end
            true, // boomerang
            nbFrameInAnimation // fps
        );
        return cancer;
    }

    Entity Creator::createBlaster(Containers::Registry &registry, size_t id, int x, int y)
    {
        const Utils::Vector2 nbFrameInSpriteSheet(6, 2);
        const uint8_t nbFrameInAnimation = 6;

        ECS::Entity blaster = ECS::Creator::createGroundedCharacter(registry, Enums::TeamGroup::ENEMY, 1, 1, 16, 15, id);
        registry.getComponents<Components::PositionComponent>().at(blaster)->x = x;
        registry.getComponents<Components::PositionComponent>().at(blaster)->y = y;
        registry.emplaceComponent<Components::DrawableComponent>(blaster,
            Assets::AssetsIndex::R_TYPESHEET12_PNG,
            nbFrameInSpriteSheet, // frameRatio
            Utils::Vector2(0, 0), // start
            Utils::Vector2(nbFrameInAnimation, 0), // end
            true, // boomerang
            nbFrameInAnimation // fps
        );
        return blaster;
    }

    Entity Creator::createAlly(Containers::Registry &registry, size_t id, int x, int y, Enums::PlayerColor color)
    {
        const Utils::Vector2 nbFrameInSpriteSheet(5, 5);
        const uint8_t nbFrameInAnimation = 5;

        ECS::Entity ally = ECS::Creator::createCharacter(registry, Enums::TeamGroup::ALLY, 1, 1, 33, 14, id);
        registry.getComponents<Components::PositionComponent>().at(ally)->x = x;
        registry.getComponents<Components::PositionComponent>().at(ally)->y = y;
        registry.emplaceComponent<Components::DrawableComponent>(ally,
            Assets::AssetsIndex::R_TYPESHEET42_PNG,
            nbFrameInSpriteSheet, // frameRatio
            Utils::Vector2(nbFrameInAnimation * (int)color, 0), // start
            Utils::Vector2(nbFrameInAnimation + (nbFrameInAnimation * (int)color), 0), // end
            true, // boomerang
            nbFrameInAnimation // fps
        );
        return ally;
    }

    Entity Creator::createPlayer(Containers::Registry &registry, size_t id, int x, int y, Enums::PlayerColor color)
    {
        Entity player = Creator::createAlly(registry, id, x, y, color);
        registry.emplaceComponent<Components::ControllableComponent>(player);
        return player;
    }

    Entity Creator::createDobkeratops(Containers::Registry &registry, size_t id, int x, int y)
    {
        const Utils::Vector2 nbFrameInSpriteSheet(4, 9);
        const uint8_t nbFrameInAnimation = 28;

        ECS::Entity dobkeratops = ECS::Creator::createCharacter(registry, Enums::TeamGroup::ENEMY, 1, 1, 155, 205, id);
        registry.getComponents<Components::PositionComponent>().at(dobkeratops)->x = x;
        registry.getComponents<Components::PositionComponent>().at(dobkeratops)->y = y;
        registry.emplaceComponent<Components::DrawableComponent>(dobkeratops,
            Assets::AssetsIndex::R_TYPESHEET30_2_PNG,
            nbFrameInSpriteSheet, // frameRatio
            Utils::Vector2(0, 2), // start
            Utils::Vector2(3, 8), // end
            true, // boomerang
            nbFrameInAnimation / 4 // fps
        );
        return dobkeratops;
    }

}; // namespace ECS
