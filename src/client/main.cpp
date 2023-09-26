/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/

#include <iostream>
#include <sys/types.h>

#include <raylib.h>

#include "ECS/containers/Registry.hpp"
#include "ECS/components/PositionComponent.hpp"
#include "ECS/components/VelocityComponent.hpp"
#include "ECS/components/DrawableComponent.hpp"
#include "ECS/components/ControllableComponent.hpp"
#include "ECS/components/HPComponent.hpp"
#include "ECS/components/DamageComponent.hpp"
#include "ECS/components/HitBoxComponent.hpp"
#include "ECS/components/MissileComponent.hpp"
#include "ECS/components/WaveBeamComponent.hpp"
#include "ECS/systems/controller.hpp"
#include "ECS/systems/movement.hpp"
#include "ECS/systems/drawable.hpp"
#include "ECS/systems/shooting.hpp"
#include "ECS/systems/helper/SpriteSheetDrawer.hpp"
#include "GameEngine/GameEngine.hpp"

using namespace ECS;

Entity spawnShip(containers::Registry &registry)
{
	const Vector2 nbFrameInSpriteSheet = Vector2(5, 5);
	const u_char nbFrameInAnimation = 5;
	Entity ship = registry.spawnEntity();
	registry.emplaceComponent<components::PositionComponent>(ship, 0, 0);
	registry.emplaceComponent<components::VelocityComponent>(ship, 0, 0);
	components::DrawableComponent drawableComponent = {
		"assets/r-typesheet42.gif",
		nbFrameInSpriteSheet, // frameRatio
		Vector2(0, 0), // start
		Vector2(nbFrameInAnimation, 0), // end
		true, // boomerang
		nbFrameInAnimation // fps
	};
	registry.addComponent<components::DrawableComponent>(ship, std::move(drawableComponent));
	return ship;
}

containers::Registry &setupRegistry(containers::Registry &registry)
{
	registry.registerComponent<components::PositionComponent>();
	registry.registerComponent<components::VelocityComponent>();
	registry.registerComponent<components::DrawableComponent>();
	registry.registerComponent<components::ControllableComponent>();
	registry.registerComponent<components::HPComponent>();
	registry.registerComponent<components::DamageComponent>();
	registry.registerComponent<components::HitBoxComponent>();
	registry.registerComponent<components::MissileComponent>();
	registry.registerComponent<components::WaveBeamComponent>();

	registry.addSystem<components::PositionComponent, components::VelocityComponent, components::ControllableComponent>(systems::controller);
	registry.addSystem<components::PositionComponent, components::VelocityComponent>(systems::movement);
	registry.addSystem<components::PositionComponent, components::DrawableComponent>(systems::drawable);
	registry.addSystem<components::MissileComponent, components::WaveBeamComponent>(systems::shooting);
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
	GameEngine::GameEngine engine;
	engine.createRegistry("entities");
	containers::Registry &registry = engine["entities"];
	registry = setupRegistry(registry);

	Entity player = spawnShip(registry);
	registry.emplaceComponent<components::ControllableComponent>(player);
	registry.getComponents<components::PositionComponent>().at(player)->x = GetScreenWidth() / 2;
	registry.getComponents<components::PositionComponent>().at(player)->y = GetScreenHeight() / 2;

	const int nbEnemies = 10;
	for (int i = 0; i < nbEnemies; i++) {
		const u_int velocityRange = 200;
		const u_char nbFrameInAnimation = 5;
		Entity entity = spawnShip(registry);
		registry.emplaceComponent<components::PositionComponent>(entity, GetRandomValue(ballRadius, GetScreenWidth() - ballRadius), GetRandomValue(ballRadius, GetScreenHeight() - ballRadius));
		registry.emplaceComponent<components::VelocityComponent>(entity, GetRandomValue(-velocityRange, velocityRange), GetRandomValue(-velocityRange, velocityRange));
		registry.getComponents<components::DrawableComponent>().at(entity)->frame = GetRandomValue(0, nbFrameInAnimation);
	}
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		registry.runSystems();
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
