/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** createServerEngine
*/

#include <functional>

#include "GameEngine/GameEngine.hpp"
#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Components/TeamComponent.hpp"

namespace GameEngine {
    namespace Containers = ECS::Containers;
    namespace Components = ECS::Components;

    static void initEntitiesRegistry(Containers::Registry &registry, ServerEventHandler serverEventHandler)
    {
        registry.addSystem<Components::PositionComponent, Components::VelocityComponent, Components::TeamComponent>(serverEventHandler);
    }

    GameEngine createServerEngine(ServerEventHandler serverEventHandler)
    {
        GameEngine engine = createEngine();

        initEntitiesRegistry(engine[registryTypeEntities], serverEventHandler);
        return engine;
    }

};
