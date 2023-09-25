/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** GameEngine
*/

#include <gtest/gtest.h>

#include "gameEngine/GameEngine.hpp"
#include "ECS/containers/SparseArray.hpp"

using namespace gameEngine;

TEST(GameEngine, creatingRegistry)
{
	GameEngine engine;

	engine.createRegistry("test");
	ASSERT_NO_THROW(engine["test"]);
}

TEST(GameEngine, gettingNonExistingRegistry)
{
	GameEngine engine;

	ASSERT_THROW(engine["test"], GameEngine::RegistryNotFound);
}

TEST(GameEngine, RegistriesAreEditable)
{
	GameEngine engine;

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
	ECS::containers::Registry &registry,
	ECS::containers::SparseArray<TestComponent> &components)
{
	for (auto &component : components) {
		component->value++;
	}
}

void testSystem2(
	ECS::containers::Registry &registry,
	ECS::containers::SparseArray<TestComponent> &components)
{
	for (auto &component : components) {
		component->value2 = true;
	}
}

TEST(GameEngine, RegistriesCanBeRun)
{
	GameEngine engine;

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
