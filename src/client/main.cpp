/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/

#include <iostream>
#include <sys/types.h>

#include <raylib.h>

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
#include "ECS/Systems/controller.hpp"
#include "ECS/Systems/movement.hpp"
#include "ECS/Systems/drawable.hpp"
#include "ECS/Systems/shooting.hpp"
#include "ECS/Systems/Helper/SpriteSheetDrawer.hpp"
#include "GameEngine/GameEngine.hpp"

using namespace ECS;

Entity spawnShip(Containers::Registry &registry)
{
	const Vector2 nbFrameInSpriteSheet = Vector2(5, 5);
	const u_char nbFrameInAnimation = 5;
	Entity ship = registry.spawnEntity();
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
	return ship;
}

Containers::Registry &setupRegistry(Containers::Registry &registry)
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

	registry.addSystem<Components::PositionComponent, Components::VelocityComponent, Components::ControllableComponent>(Systems::controller);
	registry.addSystem<Components::PositionComponent, Components::VelocityComponent>(Systems::movement);
	registry.addSystem<Components::PositionComponent, Components::DrawableComponent>(Systems::drawable);
	registry.addSystem<Components::MissileComponent, Components::WaveBeamComponent>(Systems::shooting);
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
	Containers::Registry &registry = engine["entities"];
	registry = setupRegistry(registry);

	Entity player = spawnShip(registry);
	registry.emplaceComponent<Components::ControllableComponent>(player);
	registry.getComponents<Components::PositionComponent>().at(player)->x = GetScreenWidth() / 2;
	registry.getComponents<Components::PositionComponent>().at(player)->y = GetScreenHeight() / 2;

	const int nbEnemies = 10;
	for (int i = 0; i < nbEnemies; i++) {
		const u_int velocityRange = 200;
		const u_char nbFrameInAnimation = 5;
		Entity entity = spawnShip(registry);
		registry.emplaceComponent<Components::PositionComponent>(entity, GetRandomValue(ballRadius, GetScreenWidth() - ballRadius), GetRandomValue(ballRadius, GetScreenHeight() - ballRadius));
		registry.emplaceComponent<Components::VelocityComponent>(entity, GetRandomValue(-velocityRange, velocityRange), GetRandomValue(-velocityRange, velocityRange));
		registry.getComponents<Components::DrawableComponent>().at(entity)->frame = GetRandomValue(0, nbFrameInAnimation);
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
