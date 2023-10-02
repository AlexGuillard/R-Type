/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** createEngine
*/

#include "GameEngine/GameEngine.hpp"
#include "ECS/Containers/Registry.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Components/DrawableComponent.hpp"
#include "ECS/Components/ControllableComponent.hpp"
#include "ECS/Components/HPComponent.hpp"
#include "ECS/Components/DamageComponent.hpp"
#include "ECS/Components/HitBoxComponent.hpp"
#include "ECS/Components/MissileComponent.hpp"
#include "ECS/Components/WaveBeamComponent.hpp"
#include "ECS/Components/CollidableComponent.hpp"
#include "ECS/Components/CollisionComponent.hpp"
#include "ECS/Systems/controller.hpp"
#include "ECS/Systems/movement.hpp"
#include "ECS/Systems/drawable.hpp"
#include "ECS/Systems/shooting.hpp"
#include "ECS/Systems/collision.hpp"

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

        registry.addSystem<Components::PositionComponent, Components::VelocityComponent, Components::ControllableComponent>(Systems::controller);
        registry.addSystem<Components::PositionComponent, Components::VelocityComponent>(Systems::movement);
        registry.addSystem<Components::PositionComponent, Components::DrawableComponent>(Systems::drawable);
        registry.addSystem<Components::MissileComponent, Components::WaveBeamComponent>(Systems::shooting);
        registry.addSystem<Components::PositionComponent, Components::HitBoxComponent, Components::CollidableComponent, Components::CollisionComponent>(Systems::collision);
    }

    static ECS::Entity spawnShip(Containers::Registry &registry)
    {
        const Vector2 nbFrameInSpriteSheet = Vector2(5, 5);
        const u_char nbFrameInAnimation = 5;
        ECS::Entity ship = registry.spawnEntity();
        registry.emplaceComponent<Components::PositionComponent>(ship, 0, 0);
        registry.emplaceComponent<Components::VelocityComponent>(ship, 0, 0);
        Components::DrawableComponent drawableComponent = {
            "assets/r-typesheet42.gif",
            nbFrameInSpriteSheet, // frameRatio
            Vector2(0, 0), // start
            Vector2(nbFrameInAnimation, 0), // end
            true, // boomerang
            nbFrameInAnimation // fps
        };
        registry.addComponent<Components::DrawableComponent>(ship, std::move(drawableComponent));
        registry.emplaceComponent<Components::CollidableComponent>(ship);
        const Vector2 hitboxSize = Vector2(32, 16);
        registry.emplaceComponent<Components::HitBoxComponent>(ship, hitboxSize.x, hitboxSize.y);
        return ship;
    }

    static void populateEntities(Containers::Registry &registry)
    {
        ECS::Entity player = spawnShip(registry);
        registry.emplaceComponent<Components::ControllableComponent>(player);
        registry.getComponents<Components::PositionComponent>().at(player)->x = GetScreenWidth() / 2;
        registry.getComponents<Components::PositionComponent>().at(player)->y = GetScreenHeight() / 2;
    }

    GameEngine createEngine()
    {
        GameEngine engine;
        // engine.createRegistry(RegistryType::Background);
        engine.createRegistry(registryTypeEntities);
        initEntitiesRegistry(engine.getRegistry(registryTypeEntities));
        populateEntities(engine.getRegistry(registryTypeEntities));
        return engine;
    }

}; // namespace GameEngine