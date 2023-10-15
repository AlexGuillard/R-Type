/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** createEngine
*/

#include <cstdint>

#include "GameEngine/GameEngine.hpp"
#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/BackgroundComponent.hpp"
#include "ECS/Components/LevelComponent.hpp"
#include "ECS/Systems/controller.hpp"
#include "ECS/Systems/drawable.hpp"
#include "ECS/Systems/background.hpp"
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

        registry.addSystem<Components::PositionComponent, Components::LevelComponent, Components::BackgroundComponent>(Systems::background);
    }
    static Components::BackgroundComponent createBackground(Assets::AssetsIndex index, float scale, float speed)
    {
        Components::BackgroundComponent backgroundComponent = {
            Assets::AssetLoader::loadTexturePng(index),
            scale,
            speed
        };
        return backgroundComponent;
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
            registry.emplaceComponent<Components::PositionComponent>(level, 0, 0);
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
