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
#include "ECS/Components/DrawableComponent.hpp"
#include "ECS/Components/ControllableComponent.hpp"
#include "ECS/Components/HPComponent.hpp"
#include "ECS/Components/DamageComponent.hpp"
#include "ECS/Components/HitBoxComponent.hpp"
#include "ECS/Components/MissileComponent.hpp"
#include "ECS/Components/WaveBeamComponent.hpp"
#include "ECS/Components/CollidableComponent.hpp"
#include "ECS/Components/CollisionComponent.hpp"
#include "ECS/Components/TeamComponent.hpp"
#include "ECS/Components/SinMovementComponent.hpp"
#include "ECS/Systems/controller.hpp"
#include "ECS/Systems/movement.hpp"
#include "ECS/Systems/shooting.hpp"
#include "ECS/Systems/collision.hpp"
#include "ECS/Systems/damage.hpp"
#include "ECS/Systems/sinMovement.hpp"
#include "ECS/Systems/solid.hpp"

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
        registry.registerComponent<Components::SolidComponent>();

        registry.addSystem<Components::PositionComponent, Components::VelocityComponent, Components::ControllableComponent>(Systems::controller);
        registry.addSystem<Components::PositionComponent, Components::VelocityComponent>(Systems::movement);
        registry.addSystem<Components::MissileComponent, Components::WaveBeamComponent>(Systems::shooting);
        registry.addSystem<Components::PositionComponent, Components::HitBoxComponent, Components::CollidableComponent, Components::CollisionComponent>(Systems::collision);
        registry.addSystem<Components::CollisionComponent, Components::DamageComponent, Components::TeamComponent, Components::HPComponent>(Systems::damage);
        registry.addSystem<Components::SinMovementComponent, Components::PositionComponent>(Systems::sinMovement);
        registry.addSystem<Components::SolidComponent, Components::HitBoxComponent, Components::CollisionComponent, Components::PositionComponent, Components::VelocityComponent>(Systems::solid);
    }

    GameEngine createServerEngine()
    {
        GameEngine engine;

        engine.createRegistry(registryTypeEntities);
        initEntitiesRegistry(engine[registryTypeEntities]);
        return engine;
    }

};
