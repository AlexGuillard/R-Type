/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** Registry
*/

#include <gtest/gtest.h>

#include "ECS/containers/Registry.hpp"
#include "Errors/ComponentNotRegisteredException.hpp"

using namespace ECS::containers;

TEST(Registry, canGetRegisteredComponents)
{
	Registry registry;

	registry.registerComponent<int>();
	registry.registerComponent<std::string>();
	registry.registerComponent<float>();

	ASSERT_NO_THROW(registry.getComponents<int>());
	ASSERT_NO_THROW(registry.getComponents<std::string>());
	ASSERT_NO_THROW(registry.getComponents<float>());
}

TEST(Registry, throwsWhenGettingUnregisteredComponents)
{
	Registry registry;

	ASSERT_THROW(registry.getComponents<int>(), Errors::ComponentNotRegisteredException);
	ASSERT_THROW(registry.getComponents<std::string>(), Errors::ComponentNotRegisteredException);
	ASSERT_THROW(registry.getComponents<float>(), Errors::ComponentNotRegisteredException);
}

TEST(Registry, isComponentTheSameAfterMultipleGet)
{
	Registry registry;

	registry.registerComponent<int>();
	registry.registerComponent<std::string>();
	registry.registerComponent<float>();

	auto &intList = registry.getComponents<int>();

	intList.insertAt(0, 1);

	ASSERT_EQ(&intList, &registry.getComponents<int>());

	ASSERT_EQ(1, intList[0].value());
}

class i {};

TEST(Registry, doNotShareTheSameSparseArrayBetweenComponents)
{
	Registry registry;

	registry.registerComponent<int>();
	registry.registerComponent<std::string>();
	registry.registerComponent<i>();

	auto &intList = registry.getComponents<int>();
	auto &stringList = registry.getComponents<std::string>();
	auto &iList = registry.getComponents<i>();

	intList.insertAt(0, 1);

	ASSERT_EQ(1, intList[0].value());
	ASSERT_EQ(1, intList.size());
	ASSERT_EQ(0, stringList.size());
	ASSERT_EQ(0, iList.size());
}

TEST(Registry, spawnEntity)
{
	Registry registry;

	ECS::Entity entity = registry.spawnEntity();

	ASSERT_EQ(0, std::size_t(entity));
}

TEST(Registry, spawnMultipleEntities)
{
	Registry registry;

	ECS::Entity entity0 = registry.spawnEntity();
	ECS::Entity entity1 = registry.spawnEntity();
	ECS::Entity entity2 = registry.spawnEntity();

	ASSERT_EQ(0, std::size_t(entity0));
	ASSERT_EQ(1, std::size_t(entity1));
	ASSERT_EQ(2, std::size_t(entity2));
}

TEST(Registry, getEntityFromIndex)
{
	Registry registry;

	ECS::Entity entity0 = registry.spawnEntity();
	ECS::Entity entity1 = registry.spawnEntity();
	ECS::Entity entity2 = registry.spawnEntity();

	ASSERT_EQ(entity0, registry.entityFromIndex(0));
	ASSERT_EQ(entity1, registry.entityFromIndex(1));
	ASSERT_EQ(entity2, registry.entityFromIndex(2));
}

TEST(Registry, registryCanCreateEntityFromIndex)
{
	Registry registry;

	ASSERT_EQ(42, std::size_t(registry.entityFromIndex(42)));
	ASSERT_EQ(1337, std::size_t(registry.entityFromIndex(1337)));
}

TEST(Registry, killEntityDoesntPreventGettingEntityFromIndex)
{
	Registry registry;

	ECS::Entity entity0 = registry.spawnEntity();
	ECS::Entity entity1 = registry.spawnEntity();
	ECS::Entity entity2 = registry.spawnEntity();

	ASSERT_EQ(entity0, registry.entityFromIndex(0));
	ASSERT_EQ(entity1, registry.entityFromIndex(1));
	ASSERT_EQ(entity2, registry.entityFromIndex(2));

	registry.killEntity(entity1);

	ASSERT_EQ(entity0, registry.entityFromIndex(0));
	ASSERT_EQ(entity1, registry.entityFromIndex(1));
	ASSERT_EQ(entity2, registry.entityFromIndex(2));
}

TEST(Registry, killEntityRemovesItsComponents)
{
	Registry registry;

	registry.registerComponent<int>();
	registry.registerComponent<std::string>();

	ECS::Entity entity = registry.spawnEntity();
	std::size_t entityIndex = std::size_t(entity);

	registry.addComponent<int>(entity, 42);
	registry.addComponent<std::string>(entity, "Hello World");

	ASSERT_EQ(42, registry.getComponents<int>()[entity].value());
	ASSERT_STREQ("Hello World", registry.getComponents<std::string>()[entity].value().c_str());

	registry.killEntity(entity);

	ASSERT_FALSE(registry.getComponents<int>()[entityIndex].has_value());
	ASSERT_FALSE(registry.getComponents<std::string>()[entityIndex].has_value());
}

TEST(Registry, addComponentToOneEntity)
{
	Registry registry;

	registry.registerComponent<int>();

	ECS::Entity entity = registry.spawnEntity();

	registry.addComponent<int>(entity, 42);

	auto &intList = registry.getComponents<int>();

	ASSERT_EQ(42, intList[entity]);
}

TEST(Registry, addComponentDoesNotBleed)
{
	Registry registry;

	registry.registerComponent<int>();

	ECS::Entity entity0 = registry.spawnEntity();
	ECS::Entity entity1 = registry.spawnEntity();

	registry.addComponent<int>(entity1, 42);

	auto &intList = registry.getComponents<int>();

	ASSERT_EQ(42, intList[entity1]);
	ASSERT_FALSE(intList[entity0].has_value());
}

TEST(Registry, emplaceComponent)
{
	Registry registry;

	registry.registerComponent<std::string>();

	ECS::Entity entity = registry.spawnEntity();

	registry.emplaceComponent<std::string>(entity, "Hello World");

	auto &stringList = registry.getComponents<std::string>();

	ASSERT_STREQ("Hello World", stringList[entity].value().c_str());
}

TEST(Registry, emplaceComponentDoesNotBleed)
{
	Registry registry;

	registry.registerComponent<std::string>();

	ECS::Entity entity0 = registry.spawnEntity();
	ECS::Entity entity1 = registry.spawnEntity();

	registry.emplaceComponent<std::string>(entity1, "Hello World");

	auto &stringList = registry.getComponents<std::string>();

	ASSERT_STREQ("Hello World", stringList[entity1].value().c_str());
	ASSERT_FALSE(stringList[entity0].has_value());
}

TEST(Registry, removeComponent)
{
	Registry registry;

	registry.registerComponent<int>();

	ECS::Entity entity = registry.spawnEntity();

	registry.addComponent<int>(entity, 42);

	auto &intList = registry.getComponents<int>();

	ASSERT_EQ(42, intList[entity]);

	registry.removeComponent<int>(entity);

	ASSERT_FALSE(intList[entity].has_value());
}

TEST(Registry, removeComponentDoesNotBleed)
{
	Registry registry;

	registry.registerComponent<int>();

	ECS::Entity entity0 = registry.spawnEntity();
	ECS::Entity entity1 = registry.spawnEntity();

	registry.addComponent<int>(entity0, 42);
	registry.addComponent<int>(entity1, 84);

	auto &intList = registry.getComponents<int>();

	ASSERT_EQ(42, intList[entity0]);
	ASSERT_EQ(84, intList[entity1]);

	registry.removeComponent<int>(entity1);

	ASSERT_EQ(42, intList[entity0]);
	ASSERT_FALSE(intList[entity1].has_value());
}

TEST(Registry, throwsWhenRemovingUnregisteredComponent)
{
	Registry registry;

	registry.registerComponent<int>();

	ECS::Entity entity = registry.spawnEntity();

	ASSERT_THROW(registry.removeComponent<std::string>(entity), Errors::ComponentNotRegisteredException);
}
