/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** shooting
*/

#include <string>
#include <cstring>
#include <sys/types.h>

#include <raylib.h>

#include "ECS/systems/shooting.hpp"
#include "ECS/components/PositionComponent.hpp"
#include "ECS/components/VelocityComponent.hpp"
#include "ECS/components/DamageComponent.hpp"
#include "ECS/components/HPComponent.hpp"
#include "ECS/components/DrawableComponent.hpp"
#include "ECS/containers/zipper/IndexedZipper.hpp"

namespace ECS::systems {

	/**
	 * @brief Get the Drawable For Missile object
	 * @return components::DrawableComponent
	 */
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

	/**
	 * @brief Spawns missiles from missile requests
	 * @param registry Registry into which the missiles will be spawned
	 * @param missileRequests SparseArray of missile requests
	 */
	static void shootMissiles(
		containers::Registry &registry,
		containers::SparseArray<components::MissileComponent> &missileRequests)
	{
		for (auto &&[entityId, missileRequest] : containers::IndexedZipper(missileRequests)) {
			auto missileEntity = registry.spawnEntity();

			registry.emplaceComponent<components::PositionComponent>(
				missileEntity,
				missileRequest->x,
				missileRequest->y
			);
			registry.emplaceComponent<components::VelocityComponent>(
				missileEntity,
				components::missileSpeed,
				0
			);
			registry.emplaceComponent<components::DamageComponent>(
				missileEntity,
				missileRequest->damage
			);
			registry.emplaceComponent<components::HPComponent>(
				missileEntity,
				0 // Die on collision
			);
			// TODO: add TeamComponent
			components::DrawableComponent drawable = getDrawableForMissile();
			registry.addComponent<components::DrawableComponent>(
				missileEntity, std::move(drawable)
			);
			auto entity = registry.entityFromIndex(entityId);
			registry.removeComponent<components::MissileComponent>(entity);
		}
	}

	/**
	 * @brief Get the Drawable For Wave Beam object
	 * @param strength Number between 1 and 5 that represents the strength of the wave beam
	 * @return components::DrawableComponent
	 */
	static components::DrawableComponent getDrawableForWaveBeam(u_char strength)
	{
		const u_char nbFrameInSpriteSheet = 6;
		const Vector2 waveBeamFramePos = Vector2(3, 0);
		char path[components::maxTexturePathSize] = "assets/missiles/waveBeam-out";
		components::DrawableComponent drawable = {
				"assets/missiles/waveBeam-out",
				Vector2(nbFrameInSpriteSheet, 1), // frameRatio
				waveBeamFramePos, // start
				waveBeamFramePos // end
		};
		std::strcat(drawable.texture, (std::to_string(strength) + ".png").c_str());
		return drawable;
	}

	/**
	 * @brief Spawns wave beams from wave beam requests
	 * @param registry Registry into which the wave beams will be spawned
	 * @param waveBeamRequests SparseArray of wave beam requests
	 */
	static void shootWaveBeams(
		containers::Registry &registry,
		containers::SparseArray<components::WaveBeamComponent> &waveBeamRequests)
	{
		for (auto &&[entityId, waveBeamRequests] : containers::IndexedZipper(waveBeamRequests)) {
			auto waveBeamEntity = registry.spawnEntity();

			registry.emplaceComponent<components::PositionComponent>(
				waveBeamEntity,
				waveBeamRequests->x,
				waveBeamRequests->y
			);
			registry.emplaceComponent<components::VelocityComponent>(
				waveBeamEntity,
				components::waveBeamSpeed,
				0
			);
			registry.emplaceComponent<components::DamageComponent>(
				waveBeamEntity,
				waveBeamRequests->damage
			);
			// TODO: add TeamComponent
			components::DrawableComponent drawable = getDrawableForWaveBeam(waveBeamRequests->strength);
			registry.addComponent<components::DrawableComponent>(
				waveBeamEntity, std::move(drawable)
			);
			auto entity = registry.entityFromIndex(entityId);
			registry.removeComponent<components::WaveBeamComponent>(entity);
		}
	}

	void shooting(
		containers::Registry &registry,
		containers::SparseArray<components::MissileComponent> &missileRequests,
		containers::SparseArray<components::WaveBeamComponent> &waveBeamRequests
	)
	{
		shootMissiles(registry, missileRequests);
		shootWaveBeams(registry, waveBeamRequests);
	}
}; // namespace ECS::systems
