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
#include "ECS/Components/TeamComponent.hpp"
#include "ECS/Components/BydoShootingAIComponent.hpp"
#include "ECS/Components/InRangeComponent.hpp"
#include "Assets/generatedAssets.hpp"
#include "enums.hpp"
#include "constants.hpp"
#include "GameEngine/Events.hpp"

namespace ECS {

    float Creator::mLevelScrollSpeed = Constants::defaultScrollSpeed;

    Entity Creator::addSinMovementAI(
        const Entity &entity,
        Containers::Registry &registry,
        float x,
        float y,
        float frequency,
        float speed,
        float amplitude
    )
    {
        registry.emplaceComponent<Components::SinMovementComponent>(entity);
        registry.getComponents<Components::SinMovementComponent>().at(entity)->horizontalOffset = x;
        registry.getComponents<Components::SinMovementComponent>().at(entity)->verticalOffset = y;
        if (frequency >= 0) {
            registry.getComponents<Components::SinMovementComponent>().at(entity)->frequency = frequency;
        }
        if (speed >= 0) {
            registry.getComponents<Components::SinMovementComponent>().at(entity)->speed = speed;
        }
        if (amplitude >= 0) {
            registry.getComponents<Components::SinMovementComponent>().at(entity)->amplitude = amplitude;
        }
        return entity;
    }

    Entity Creator::addWalkingAI(
        const Entity &entity,
        Containers::Registry &registry,
        const Entity &target,
        std::pair<float, float> preferredDistance,
        float speed,
        bool dropsDownLedge,
        bool jumpsOverObstacle)
    {
        registry.emplaceComponent<Components::WalkingAIComponent>(entity, preferredDistance, speed, dropsDownLedge, jumpsOverObstacle);
        registry.emplaceComponent<Components::TargetComponent>(entity, static_cast<std::size_t>(target));
        registry.emplaceComponent<Components::GravityComponent>(entity, Creator::defaultGravity);
        registry.emplaceComponent<Components::CollidableComponent>(entity);
        return entity;
    }

    Entity Creator::addBydoShootingAI(
        const Entity &entity,
        Containers::Registry &registry,
        const Entity &target,
        float shootCooldown,
        float shotSpeed
    )
    {
        registry.emplaceComponent<Components::BydoShootingAIComponent>(entity, shootCooldown, shotSpeed);
        registry.emplaceComponent<Components::TargetComponent>(entity, static_cast<std::size_t>(target));
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

    Entity Creator::createBydoShot(
        Containers::Registry &registry,
        float x,
        float y,
        float xDirection,
        float yDirection,
        Enums::TeamGroup team
    )
    {
        Entity shot = Creator::createCharacter(
            registry,
            team,
            1, // damage
            0, // hp: dies on collision
            7, // width
            7 // height
        );
        registry.emplaceComponent<Components::PositionComponent>(shot, x, y);
        registry.emplaceComponent<Components::VelocityComponent>(shot, xDirection, yDirection);
        registry.emplaceComponent<Components::DrawableComponent>(shot,
            Assets::AssetsIndex::BYDO_SHOT_PNG,
            Utils::Vector2(4, 1), // frameRatio
            Utils::Vector2(0, 0), // start
            Utils::Vector2(4, 0), // end
            false, // boomerang
            4 // fps
        );
        registry.emplaceComponent<Components::CollidableComponent>(shot);
        return shot;
    }

    Entity Creator::createMissile(Containers::Registry &registry, size_t id, int x, int y, Enums::TeamGroup team)
    {
        const Utils::Vector2 missileFramePos(2, 0);
        const uint8_t nbFrameInSpriteSheet = 6;

        ECS::Entity missile = ECS::Creator::createCharacter(registry, team, 1, 0, 16, 16, id);
        registry.getComponents<Components::PositionComponent>().at(missile)->x = x;
        registry.getComponents<Components::PositionComponent>().at(missile)->y = y;
        registry.getComponents<Components::VelocityComponent>().at(missile)->y = 0;
        if (Enums::TeamGroup::ALLY == team) {
            registry.getComponents<Components::VelocityComponent>().at(missile)->x = Components::missileSpeed;
            registry.emplaceComponent<Components::DrawableComponent>(missile,
                Assets::AssetsIndex::MISSILE_PNG,
                Utils::Vector2(nbFrameInSpriteSheet, 1), // frameRatio
                missileFramePos, // start
                missileFramePos // end
            );
        } else {
            registry.getComponents<Components::VelocityComponent>().at(missile)->x = -Components::missileSpeed;
            registry.emplaceComponent<Components::DrawableComponent>(missile,
                Assets::AssetsIndex::MISSILE_PNG,
                Utils::Vector2(nbFrameInSpriteSheet, 1), // frameRatio
                Utils::Vector2(3, 0), // start
                Utils::Vector2(3, 0) // end
            );
        }
        GameEngine::Events::push(GameEngine::Events::Type::PLAYER_MISSILE, id);
        return missile;
    }

    Entity Creator::createWaveBeam(Containers::Registry &registry, size_t id, int x, int y, Enums::TeamGroup team, int strength)
    {
        const Utils::Vector2 missileFramePos(2, 0);
        const uint8_t nbFrameInSpriteSheet = 2;

        ECS::Entity wavebeam = ECS::Creator::createCharacter(registry, team, 2 * strength, 0, 16 * strength + 1, 12, id);
        registry.getComponents<Components::PositionComponent>().at(wavebeam)->x = x;
        registry.getComponents<Components::PositionComponent>().at(wavebeam)->y = y;
        registry.getComponents<Components::VelocityComponent>().at(wavebeam)->y = 0;
        if (Enums::TeamGroup::ALLY == team) {
            registry.getComponents<Components::VelocityComponent>().at(wavebeam)->x = Components::missileSpeed;
            switch (strength) {
            case 2:
                registry.emplaceComponent<Components::DrawableComponent>(wavebeam,
                    Assets::AssetsIndex::WAVEBEAM_OUT2_PNG,
                    Utils::Vector2(nbFrameInSpriteSheet, 1), // frameRatio
                    missileFramePos, // start
                    missileFramePos // end
                );
                break;
            case 3:
                registry.emplaceComponent<Components::DrawableComponent>(wavebeam,
                    Assets::AssetsIndex::WAVEBEAM_OUT3_PNG,
                    Utils::Vector2(nbFrameInSpriteSheet, 1), // frameRatio
                    missileFramePos, // start
                    missileFramePos // end
                );
                break;
            case 4:
                registry.emplaceComponent<Components::DrawableComponent>(wavebeam,
                    Assets::AssetsIndex::WAVEBEAM_OUT4_PNG,
                    Utils::Vector2(nbFrameInSpriteSheet, 1), // frameRatio
                    missileFramePos, // start
                    missileFramePos // end
                );
                break;
            case 5:
                registry.emplaceComponent<Components::DrawableComponent>(wavebeam,
                    Assets::AssetsIndex::WAVEBEAM_OUT5_PNG,
                    Utils::Vector2(nbFrameInSpriteSheet, 1), // frameRatio
                    missileFramePos, // start
                    missileFramePos // end
                );
                break;
            default:
                registry.emplaceComponent<Components::DrawableComponent>(wavebeam,
                    Assets::AssetsIndex::WAVEBEAM_OUT1_PNG,
                    Utils::Vector2(nbFrameInSpriteSheet, 1), // frameRatio
                    missileFramePos, // start
                    missileFramePos // end
                );
                break;
            }
        } else {
            registry.getComponents<Components::VelocityComponent>().at(wavebeam)->x = -Components::missileSpeed;
            switch (strength) {
            case 2:
                registry.emplaceComponent<Components::DrawableComponent>(wavebeam,
                    Assets::AssetsIndex::WAVEBEAM_FLARE2_PNG,
                    Utils::Vector2(nbFrameInSpriteSheet, 1), // frameRatio
                    missileFramePos, // start
                    missileFramePos // end
                );
                break;
            case 3:
                registry.emplaceComponent<Components::DrawableComponent>(wavebeam,
                    Assets::AssetsIndex::WAVEBEAM_FLARE3_PNG,
                    Utils::Vector2(nbFrameInSpriteSheet, 1), // frameRatio
                    missileFramePos, // start
                    missileFramePos // end
                );
                break;
            case 4:
                registry.emplaceComponent<Components::DrawableComponent>(wavebeam,
                    Assets::AssetsIndex::WAVEBEAM_FLARE4_PNG,
                    Utils::Vector2(nbFrameInSpriteSheet, 1), // frameRatio
                    missileFramePos, // start
                    missileFramePos // end
                );
                break;
            case 5:
                registry.emplaceComponent<Components::DrawableComponent>(wavebeam,
                    Assets::AssetsIndex::WAVEBEAM_FLARE5_PNG,
                    Utils::Vector2(3, 1), // frameRatio
                    Utils::Vector2(0, 0), // start
                    Utils::Vector2(0, 0) // end
                );
                break;
            default:
                registry.emplaceComponent<Components::DrawableComponent>(wavebeam,
                    Assets::AssetsIndex::WAVEBEAM_FLARE1_PNG,
                    Utils::Vector2(nbFrameInSpriteSheet, 1), // frameRatio
                    missileFramePos, // start
                    missileFramePos // end
                );
                break;
            }
        }
        return wavebeam;
    }

    Entity Creator::createEnemyBasic(Containers::Registry &registry, size_t id, int x, int y)
    {
        const Utils::Vector2 nbFrameInSpriteSheet(16, 1);
        const uint8_t nbFrameInAnimation = 8;

        ECS::Entity enemyBasic = ECS::Creator::createCharacter(registry, Enums::TeamGroup::ENEMY, 1, 1, 20, 24, id);
        registry.emplaceComponent<Components::PositionComponent>(enemyBasic, x, y);
        addSinMovementAI(enemyBasic, registry, x, y);
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
        Creator::addWalkingAI(bink, registry, ECS::NullEntity(), std::make_pair(0.F, 500.F), 100, true, false);
        Creator::addBydoShootingAI(bink, registry, ECS::NullEntity(), 1, 100);
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
        addSinMovementAI(bug, registry, x, y, Components::defaultSinFrequency * 2, Components::defaultSinXSpeed * 2, Components::defaultSinAmplitude * 2);
        addBydoShootingAI(bug, registry, ECS::NullEntity(), 1.5F, 100);
        registry.emplaceComponent<Components::InRangeComponent>(bug);
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
        registry.emplaceComponent<Components::GravityComponent>(blaster, Creator::defaultGravity);
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
