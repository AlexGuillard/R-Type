/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** GameEngine
*/

#include <gtest/gtest.h>

#include "GameEngine/GameEngine.hpp"
#include "ECS/Containers/SparseArray.hpp"
#include "Errors/RegistryNotFound.hpp"

TEST(GameEngineT, creatingRegistry)
{
	GameEngine::GameEngine engine;

	engine.createRegistry("test");
	ASSERT_NO_THROW(engine["test"]);
}

TEST(GameEngineT, gettingNonExistingRegistry)
{
	GameEngine::GameEngine engine;

	ASSERT_THROW(engine["test"], Errors::RegistryNotFound);
}

TEST(GameEngineT, RegistriesAreEditable)
{
	GameEngine::GameEngine engine;

	engine.createRegistry("test");
	auto &registry = engine["test"];
	registry.spawnEntity();
	ASSERT_EQ(registry.size(), 1);
}

struct TestComponent {
	int value = 0;
	bool value2 = false;
};

void testSystem(
	ECS::Containers::Registry &registry,
	ECS::Containers::SparseArray<TestComponent> &components)
{
	for (auto &component : components) {
		component->value++;
	}
}

void testSystem2(
	ECS::Containers::Registry &registry,
	ECS::Containers::SparseArray<TestComponent> &components)
{
	for (auto &component : components) {
		component->value2 = true;
	}
}

TEST(GameEngineT, RegistriesCanBeRun)
{
	GameEngine::GameEngine engine;

	engine.createRegistry("test");
	auto &registry = engine["test"];
	registry.registerComponent<TestComponent>();
	registry.addSystem<TestComponent>(testSystem);
	registry.addSystem<TestComponent>(testSystem2);
	registry.spawnEntity();
	auto &component = registry.getComponents<TestComponent>().at(0);
	ASSERT_EQ(component->value, 0);
	ASSERT_FALSE(component->value2);
	engine.run();
	ASSERT_EQ(component->value, 1);
	ASSERT_TRUE(component->value2);
}
