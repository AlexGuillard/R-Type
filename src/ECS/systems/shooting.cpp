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
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Components/DamageComponent.hpp"
#include "ECS/Components/HPComponent.hpp"
#include "ECS/Components/DrawableComponent.hpp"
#include "ECS/Containers/zipper/IndexedZipper.hpp"

namespace ECS::systems {

	/**
	 * @brief Get the Drawable For Missile object
	 * @return Components::DrawableComponent
	 */
	static Components::DrawableComponent getDrawableForMissile()
	{
		const u_char nbFrameInSpriteSheet = 6;
		const Vector2 missileFramePos = Vector2(2, 0);
		Components::DrawableComponent drawable = {
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
		Containers::Registry &registry,
		Containers::SparseArray<Components::MissileComponent> &missileRequests)
	{
		for (auto &&[entityId, missileRequest] : Containers::IndexedZipper(missileRequests)) {
			auto missileEntity = registry.spawnEntity();

			registry.emplaceComponent<Components::PositionComponent>(
				missileEntity,
				missileRequest->x,
				missileRequest->y
			);
			registry.emplaceComponent<Components::VelocityComponent>(
				missileEntity,
				Components::missileSpeed,
				0
			);
			registry.emplaceComponent<Components::DamageComponent>(
				missileEntity,
				missileRequest->damage
			);
			registry.emplaceComponent<Components::HPComponent>(
				missileEntity,
				0 // Die on collision
			);
			// TODO: add TeamComponent
			Components::DrawableComponent drawable = getDrawableForMissile();
			registry.addComponent<Components::DrawableComponent>(
				missileEntity, std::move(drawable)
			);
			auto entity = registry.entityFromIndex(entityId);
			registry.removeComponent<Components::MissileComponent>(entity);
		}
	}

	/**
	 * @brief Get the Drawable For Wave Beam object
	 * @param strength Number between 1 and 5 that represents the strength of the wave beam
	 * @return Components::DrawableComponent
	 */
	static Components::DrawableComponent getDrawableForWaveBeam(u_char strength)
	{
		const u_char nbFrameInSpriteSheet = 6;
		const Vector2 waveBeamFramePos = Vector2(3, 0);
		char path[Components::maxTexturePathSize] = "assets/missiles/waveBeam-out";
		Components::DrawableComponent drawable = {
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
		Containers::Registry &registry,
		Containers::SparseArray<Components::WaveBeamComponent> &waveBeamRequests)
	{
		for (auto &&[entityId, waveBeamRequests] : Containers::IndexedZipper(waveBeamRequests)) {
			auto waveBeamEntity = registry.spawnEntity();

			registry.emplaceComponent<Components::PositionComponent>(
				waveBeamEntity,
				waveBeamRequests->x,
				waveBeamRequests->y
			);
			registry.emplaceComponent<Components::VelocityComponent>(
				waveBeamEntity,
				Components::waveBeamSpeed,
				0
			);
			registry.emplaceComponent<Components::DamageComponent>(
				waveBeamEntity,
				waveBeamRequests->damage
			);
			// TODO: add TeamComponent
			Components::DrawableComponent drawable = getDrawableForWaveBeam(waveBeamRequests->strength);
			registry.addComponent<Components::DrawableComponent>(
				waveBeamEntity, std::move(drawable)
			);
			auto entity = registry.entityFromIndex(entityId);
			registry.removeComponent<Components::WaveBeamComponent>(entity);
		}
	}

	void shooting(
		Containers::Registry &registry,
		Containers::SparseArray<Components::MissileComponent> &missileRequests,
		Containers::SparseArray<Components::WaveBeamComponent> &waveBeamRequests
	)
	{
		shootMissiles(registry, missileRequests);
		shootWaveBeams(registry, waveBeamRequests);
	}
}; // namespace ECS::systems
