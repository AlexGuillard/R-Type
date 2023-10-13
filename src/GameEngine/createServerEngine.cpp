/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** createServerEngine
*/

#include "GameEngine/GameEngine.hpp"

#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Systems/serverEventHandler.hpp"

namespace GameEngine {
    namespace Containers = ECS::Containers;
    namespace Components = ECS::Components;
    namespace Systems = ECS::Systems;

    static void initEntitiesRegistry(Containers::Registry &registry)
    {
        registry.addSystem<Components::PositionComponent, Components::VelocityComponent>(Systems::serverEventHandler);
    }

    GameEngine createServerEngine()
    {
        GameEngine engine = createEngine();

        initEntitiesRegistry(engine[registryTypeEntities]);
        return engine;
    }

};
