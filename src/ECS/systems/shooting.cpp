/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** shooting
*/

#include <raylib.h>

#include "ECS/systems/shooting.hpp"
#include "ECS/components/PositionComponent.hpp"
#include "ECS/components/VelocityComponent.hpp"
#include "ECS/components/DamageComponent.hpp"
#include "ECS/components/HPComponent.hpp"
#include "ECS/components/DrawableComponent.hpp"
#include "ECS/containers/zipper/IndexedZipper.hpp"

#include <iostream>
namespace ECS::systems {

	static components::DrawableComponent getDrawableForMissile()
	{
		const u_char nbFrameInSpriteSheet = 6;
		const Vector2 missileFramePos = Vector2(2, 0);
		components::DrawableComponent drawable = {
				"assets/missiles/missile.png",
				Vector2(nbFrameInSpriteSheet, 1), // frameRatio
				missileFramePos, // start
				missileFramePos // end
		};
		return drawable;
	}

	static void shootMissiles(
		containers::Registry &registry,
		containers::SparseArray<components::MissileComponent> &missileRequests)
	{
		for (auto &&[entityId, missileRequest] : containers::IndexedZipper(missileRequests)) {
			std::cout << "shooting" << std::endl;
			auto bulletEntity = registry.spawnEntity();

			registry.emplaceComponent<components::PositionComponent>(
				bulletEntity,
				missileRequest->x,
				missileRequest->y
			);
			registry.emplaceComponent<components::VelocityComponent>(
				bulletEntity,
				components::missileSpeed,
				0
			);
			registry.emplaceComponent<components::DamageComponent>(
				bulletEntity,
				missileRequest->damage
			);
			registry.emplaceComponent<components::HPComponent>(
				bulletEntity,
				0 // Die on collision
			);
			components::DrawableComponent drawable = getDrawableForMissile();
			registry.addComponent<components::DrawableComponent>(
				bulletEntity, std::move(drawable)
			);
			auto entity = registry.entityFromIndex(entityId);
			registry.removeComponent<components::MissileComponent>(entity);
		}
	}

	void shooting(
		containers::Registry &registry,
		containers::SparseArray<components::MissileComponent> &missileRequests,
		containers::SparseArray<components::WaveBeamComponent> &waveBeamRequests
	)
	{
		shootMissiles(registry, missileRequests);
		(void)waveBeamRequests;
	}
}; // namespace ECS::systems
