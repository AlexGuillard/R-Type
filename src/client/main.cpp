/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/

#include <iostream>

#include <raylib.h>

#include "ECS/containers/Registry.hpp"
#include "ECS/components/PositionComponent.hpp"
#include "ECS/components/VelocityComponent.hpp"
#include "ECS/components/DrawableComponent.hpp"
#include "ECS/components/ControllableComponent.hpp"
#include "ECS/systems/controller.hpp"
#include "ECS/systems/movement.hpp"
#include "ECS/systems/drawable.hpp"
#include "ECS/systems/helper/SpriteSheetDrawer.hpp"
#include "gameEngine/GameEngine.hpp"

using namespace ECS;

Entity spawnShip(containers::Registry &registry)
{
	Entity ship = registry.spawnEntity();
	registry.emplaceComponent<components::PositionComponent>(ship, 0, 0);
	registry.emplaceComponent<components::VelocityComponent>(ship, 0, 0);
	registry.emplaceComponent<components::DrawableComponent>(ship,
		LoadTexture("assets/r-typesheet42.gif"), // texture
		Vector2(5, 5), // frameRatio
		Vector2(0, 0), // start
		Vector2(5, 0), // end
		true, // boomerang
		5 // fps
	);
	return ship;
}

containers::Registry &setupRegistry(containers::Registry &registry)
{
	registry.registerComponent<components::PositionComponent>();
	registry.registerComponent<components::VelocityComponent>();
	registry.registerComponent<components::DrawableComponent>();
	registry.registerComponent<components::ControllableComponent>();

	registry.addSystem<components::VelocityComponent, components::ControllableComponent>(systems::controller);
	registry.addSystem<components::PositionComponent, components::VelocityComponent>(systems::movement);
	registry.addSystem<components::PositionComponent, components::DrawableComponent>(systems::drawable);
	return registry;
}

void initialiseWindow()
{
	const std::size_t screenWidth = 800;
	const std::size_t screenHeight = 540;
	const std::size_t fps = 60;

	InitWindow(screenWidth, screenHeight, "R-Type");
	SetTargetFPS(fps);
	// SetExitKey(KEY_NULL); // TODO: uncomment this line to have access to the escape key
}

int main()
{
	initialiseWindow();
	const int ballRadius = 10;
	gameEngine::GameEngine engine;
	engine.createRegistry("entities");
	containers::Registry &registry = engine["entities"];
	registry = setupRegistry(registry);

	Entity player = spawnShip(registry);
	registry.emplaceComponent<components::ControllableComponent>(player);
	registry.getComponents<components::PositionComponent>().at(player)->x = GetScreenWidth() / 2;
	registry.getComponents<components::PositionComponent>().at(player)->y = GetScreenHeight() / 2;

	for (int i = 0; i < 10; i++) {
		Entity entity = spawnShip(registry);
		registry.emplaceComponent<components::PositionComponent>(entity, GetRandomValue(ballRadius, GetScreenWidth() - ballRadius), GetRandomValue(ballRadius, GetScreenHeight() - ballRadius));
		registry.emplaceComponent<components::VelocityComponent>(entity, GetRandomValue(-200, 200), GetRandomValue(-200, 200));
		registry.getComponents<components::DrawableComponent>().at(entity)->frame = GetRandomValue(0, 6);
	}
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("move the player with arrow keys", 10, 10, 20, DARKGRAY);
		registry.runSystems();
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
