/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** createEngine
*/

#include <cstdint>

#include "GameEngine/GameEngine.hpp"
#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/GroundComponent.hpp"
#include "ECS/Components/BackgroundComponent.hpp"
#include "ECS/Components/LevelComponent.hpp"
#include "ECS/Systems/controller.hpp"
#include "ECS/Systems/drawable.hpp"
#include "ECS/Systems/background.hpp"
#include "ECS/Systems/ground.hpp"
#include "Assets/generatedAssets.hpp"
#include "client/display/Display.hpp"
#include "Assets/AssetLoader.hpp"
#include "ECS/Creator.hpp"

namespace GameEngine {
    namespace Containers = ECS::Containers;
    namespace Components = ECS::Components;
    namespace Systems = ECS::Systems;

    static void initEntitiesRegistry(Containers::Registry &registry)
    {
        registry.addSystem<Components::PositionComponent, Components::VelocityComponent, Components::TeamComponent, Components::ControllableComponent>(Systems::controller);
        registry.addSystem<Components::PositionComponent, Components::DrawableComponent>(Systems::drawable); // keep last
    }

    static void initLevelRegistry(Containers::Registry &registry)
    {
        registry.registerComponent<Components::BackgroundComponent>();
        registry.registerComponent<Components::LevelComponent>();
        registry.registerComponent<Components::PositionComponent>();
        registry.registerComponent<Components::GroundComponent>();

        registry.addSystem<Components::PositionComponent, Components::LevelComponent, Components::BackgroundComponent>(Systems::background);
        registry.addSystem<Components::PositionComponent, Components::LevelComponent, Components::GroundComponent>(Systems::ground);
    }
    static Components::BackgroundComponent createBackground(Assets::AssetsIndex index, double fps)
    {
        Components::BackgroundComponent backgroundComponent = {
            index,
            1,
            1.0,
            fps
        };
        return backgroundComponent;
    }

    static Components::GroundComponent createGround(Assets::AssetsIndex index, std::vector<double> sizeSpeed)
    {
        Components::GroundComponent groundComponent = {
            index,
            sizeSpeed[0],
            sizeSpeed[1],
            sizeSpeed[2]
        };
        return groundComponent;
    }


    static void populateEntities(Containers::Registry &registry)
    {}

        static void levelEntities(Containers::Registry &registry, int _level)
    {
        std::vector<Assets::AssetsIndex> assetIndices = {
            Assets::AssetsIndex::BACKGROUND1_PNG,
            Assets::AssetsIndex::BACKGROUND2_PNG,
            Assets::AssetsIndex::BACKGROUND3_PNG,
            Assets::AssetsIndex::BACKGROUND4_PNG,
        };

        std::vector<double> fps = {
            double(0.015),
            double(0.010),
            double(0.005),
            double(0.002)
        };

        for (size_t i = 0; i < assetIndices.size(); ++i)
        {
            Components::BackgroundComponent background = createBackground(assetIndices[i], fps[i]);
            Components::GroundComponent ground = createGround(Assets::AssetsIndex::GROUND1_PNG,  {double(3.0), double(1.0), double(0.020)});
            ECS::Entity level = registry.spawnEntity();
            registry.emplaceComponent<Components::BackgroundComponent>(level, background);
            registry.emplaceComponent<Components::LevelComponent>(level, _level);
            registry.emplaceComponent<Components::PositionComponent>(level, 0, 0);
            registry.emplaceComponent<Components::GroundComponent>(level, ground);
            registry.emplaceComponent<Components::PositionComponent>(level, 0, Constants::cameraDefaultHeight * (1 - 0.1));
        }
    }

    GameEngine createClientEngine()
    {
        GameEngine engine = createEngine();
        initEntitiesRegistry(engine.getRegistry(registryTypeEntities));
        initLevelRegistry(engine.getRegistry(registryTypeBackground));
        levelEntities(engine.getRegistry(registryTypeBackground), engine.getLevel());
        populateEntities(engine.getRegistry(registryTypeEntities));
        return engine;
    }

}; // namespace GameEngine
