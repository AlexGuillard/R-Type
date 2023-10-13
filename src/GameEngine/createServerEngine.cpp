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
    {}

    GameEngine createServerEngine()
    {
        GameEngine engine = createEngine();

        initEntitiesRegistry(engine[registryTypeEntities]);
        return engine;
    }

};
