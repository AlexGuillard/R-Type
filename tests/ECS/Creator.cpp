/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Creator
*/

#include <gtest/gtest.h>

#include "ECS/Creator.hpp"
#include "ECS/Components/DamageComponent.hpp"
#include "ECS/Components/HPComponent.hpp"
#include "ECS/Components/HitBoxComponent.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Components/TeamComponent.hpp"
#include "ECS/Components/CollidableComponent.hpp"
#include "ECS/Components/CollisionComponent.hpp"
#include "GameEngine/GameEngine.hpp"

using namespace ECS;

TEST(Creator, createCharacter)
{
    GameEngine::GameEngine engine = GameEngine::createEngine();
    Containers::Registry &registry = engine.getRegistry(GameEngine::registryTypeEntities);
    registry.registerComponent<Components::DamageComponent>();
    registry.registerComponent<Components::HPComponent>();
    registry.registerComponent<Components::HitBoxComponent>();
    registry.registerComponent<Components::PositionComponent>();
    registry.registerComponent<Components::VelocityComponent>();
    registry.registerComponent<Components::TeamComponent>();
    registry.registerComponent<Components::CollidableComponent>();
    registry.registerComponent<Components::CollisionComponent>();
    Entity entity = Creator::createCharacter(registry, Enums::TeamGroup::NEUTRAL, 1, 2, 3, 4);

    ASSERT_EQ(registry.getComponents<Components::DamageComponent>().at(entity)->damage, 1);
    ASSERT_EQ(registry.getComponents<Components::HPComponent>().at(entity)->hp, 2);
    ASSERT_EQ(registry.getComponents<Components::HitBoxComponent>().at(entity)->width, 3);
    ASSERT_EQ(registry.getComponents<Components::HitBoxComponent>().at(entity)->height, 4);
    ASSERT_EQ(registry.getComponents<Components::PositionComponent>().at(entity)->x, 0);
    ASSERT_EQ(registry.getComponents<Components::PositionComponent>().at(entity)->y, 0);
    ASSERT_EQ(registry.getComponents<Components::VelocityComponent>().at(entity)->x, 0);
    ASSERT_EQ(registry.getComponents<Components::VelocityComponent>().at(entity)->y, 0);
}
