/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** createEngine
*/

#include <cstdint>

#include "GameEngine/GameEngine.hpp"
#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Components/DrawableComponent.hpp"
#include "ECS/Components/ControllableComponent.hpp"
#include "ECS/Components/TeamComponent.hpp"
#include "ECS/Components/HPComponent.hpp"
#include "ECS/Components/DamageComponent.hpp"
#include "ECS/Components/HitBoxComponent.hpp"
#include "ECS/Components/MissileComponent.hpp"
#include "ECS/Components/WaveBeamComponent.hpp"
#include "ECS/Components/CollidableComponent.hpp"
#include "ECS/Components/CollisionComponent.hpp"
#include "ECS/Components/SinMovementComponent.hpp"
#include "ECS/Components/InRangeComponent.hpp"
#include "ECS/Components/WalkingAIComponent.hpp"
#include "ECS/Components/TargetComponent.hpp"
#include "ECS/Components/BackgroundComponent.hpp"
#include "ECS/Components/LevelComponent.hpp"
#include "Assets/AssetLoader.hpp"
#include "ECS/Components/GravityComponent.hpp"
#include "ECS/Components/HorizontalScrollComponent.hpp"
#include "ECS/Systems/movement.hpp"
#include "ECS/Systems/drawable.hpp"
#include "ECS/Systems/background.hpp"
#include "ECS/Systems/shooting.hpp"
#include "ECS/Systems/collision.hpp"
#include "ECS/Creator.hpp"
#include "ECS/Systems/damage.hpp"
#include "ECS/Systems/sinMovement.hpp"
#include "ECS/Systems/target.hpp"
#include "ECS/Systems/walkingAI.hpp"
#include "ECS/Systems/gravity.hpp"
#include "ECS/Systems/solid.hpp"
#include "ECS/Systems/horizontalScroll.hpp"
#include "Assets/generatedAssets.hpp"
#include "client/display/Display.hpp"

namespace GameEngine {
    namespace Containers = ECS::Containers;
    namespace Components = ECS::Components;
    namespace Systems = ECS::Systems;

    static void initEntitiesRegistry(Containers::Registry &registry)
    {
        registry.registerComponent<Components::PositionComponent>();
        registry.registerComponent<Components::VelocityComponent>();
        registry.registerComponent<Components::DrawableComponent>();
        registry.registerComponent<Components::ControllableComponent>();
        registry.registerComponent<Components::HPComponent>();
        registry.registerComponent<Components::DamageComponent>();
        registry.registerComponent<Components::HitBoxComponent>();
        registry.registerComponent<Components::MissileComponent>();
        registry.registerComponent<Components::WaveBeamComponent>();
        registry.registerComponent<Components::CollidableComponent>();
        registry.registerComponent<Components::CollisionComponent>();
        registry.registerComponent<Components::TeamComponent>();
        registry.registerComponent<Components::SinMovementComponent>();
        registry.registerComponent<Components::InRangeComponent>();
        registry.registerComponent<Components::WalkingAIComponent>();
        registry.registerComponent<Components::TargetComponent>();
        registry.registerComponent<Components::SolidComponent>();
        registry.registerComponent<Components::GravityComponent>();
        registry.registerComponent<Components::TargetComponent>();
        registry.registerComponent<Components::HorizontalScrollComponent>();

        registry.addSystem<Components::PositionComponent, Components::VelocityComponent>(Systems::movement);
        registry.addSystem<Components::MissileComponent, Components::WaveBeamComponent>(Systems::shooting);
        registry.addSystem<Components::PositionComponent, Components::HitBoxComponent, Components::CollidableComponent, Components::CollisionComponent>(Systems::collision);
        registry.addSystem<Components::CollisionComponent, Components::DamageComponent, Components::TeamComponent, Components::HPComponent>(Systems::damage);
        registry.addSystem<Components::SinMovementComponent, Components::PositionComponent>(Systems::sinMovement);
        registry.addSystem<Components::TargetComponent, Components::PositionComponent>(Systems::target);
        registry.addSystem<Components::WalkingAIComponent, Components::TargetComponent, Components::VelocityComponent, Components::CollisionComponent, Components::PositionComponent, Components::HitBoxComponent>(Systems::walkingAI);
        registry.addSystem<Components::SolidComponent, Components::HitBoxComponent, Components::CollisionComponent, Components::PositionComponent, Components::VelocityComponent>(Systems::solid);
        registry.addSystem<Components::VelocityComponent, Components::GravityComponent>(Systems::gravity);
        registry.addSystem<Components::HorizontalScrollComponent, Components::PositionComponent>(Systems::horizontalScroll);
    }

    static void initLevelRegistry(Containers::Registry &registry)
    {
        registry.registerComponent<Components::BackgroundComponent>();
        registry.registerComponent<Components::LevelComponent>();

        registry.addSystem<Components::LevelComponent, Components::BackgroundComponent>(Systems::background);
    }
    static Components::BackgroundComponent createBackground(Assets::AssetsIndex index, float scale, float speed)
    {
        const Vector2 position = {0, 0};
        Components::BackgroundComponent backgroundComponent = {
            Assets::AssetLoader::loadTexturePng(index),
            scale,
            speed,
            position,
        };
        return backgroundComponent;
    }

    static void populateEntities(Containers::Registry &registry)
    {
        // TODO: delete when client is ready
        auto &&player = ECS::Creator::createPlayer(registry, registry.spawnEntity(), 500, 500, Enums::PlayerColor::CYAN_COLOR);
        ECS::Creator::createBink(registry, registry.spawnEntity(), 1000, 500);
    }

    static void levelEntities(Containers::Registry &registry, int _level)
    {
        std::vector<Assets::AssetsIndex> assetIndices = {
            Assets::AssetsIndex::BACKGROUND1_PNG,
            Assets::AssetsIndex::BACKGROUND2_PNG,
            Assets::AssetsIndex::BACKGROUND3_PNG,
            Assets::AssetsIndex::BACKGROUND4_PNG,
        };

        std::vector<std::pair<float, float>> sizeAndSpeed = {
            {(float) 5.0, (float) 0.5},
            {(float) 1.5, (float) 1.0},
            {(float) 1.5, (float) 1.5},
            {(float) 7.0, (float) 2.0}
        };

        for (size_t i = 0; i < assetIndices.size(); ++i)
        {
            Components::BackgroundComponent background = createBackground(assetIndices[i],
            sizeAndSpeed[i].first, sizeAndSpeed[i].second);
            ECS::Entity level = registry.spawnEntity();
            registry.emplaceComponent<Components::BackgroundComponent>(level, background);
            registry.emplaceComponent<Components::LevelComponent>(level, _level);
        }
    }

    GameEngine createEngine()
    {
        GameEngine engine;
        engine.createRegistry(registryTypeBackground);
        engine.createRegistry(registryTypeEntities);
        initLevelRegistry(engine.getRegistry(registryTypeBackground));
        initEntitiesRegistry(engine.getRegistry(registryTypeEntities));
        levelEntities(engine.getRegistry(registryTypeBackground), engine.getLevel());
        populateEntities(engine.getRegistry(registryTypeEntities));
        return engine;
    }

}; // namespace GameEngine
