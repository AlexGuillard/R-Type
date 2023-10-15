/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** createEngine
*/

#include <cstdint>

#include "GameEngine/GameEngine.hpp"
#include "ECS/Containers/Registry.hpp"
#include "ECS/Systems/controller.hpp"
#include "ECS/Systems/drawable.hpp"
#include "Assets/generatedAssets.hpp"
#include "client/display/Display.hpp"
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

    static void populateEntities(Containers::Registry &registry)
    {}

    GameEngine createClientEngine()
    {
        GameEngine engine = createEngine();
        initEntitiesRegistry(engine.getRegistry(registryTypeEntities));
        populateEntities(engine.getRegistry(registryTypeEntities));
        return engine;
    }

}; // namespace GameEngine
