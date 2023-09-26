/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** controller
*/

#include <raylib.h>

#include "ECS/systems/controller.hpp"
#include "ECS/components/PositionComponent.hpp"
#include "ECS/components/VelocityComponent.hpp"
#include "ECS/components/ControllableComponent.hpp"
#include "ECS/components/WaveBeamComponent.hpp"
#include "ECS/components/MissileComponent.hpp"
#include "ECS/containers/zipper/Zipper.hpp"

namespace ECS::systems {

	template <typename T>
	static T clamp(T value, T min, T max)
	{
		if (value < min) {
			return min;
		}
		if (value > max) {
			return max;
		}
		return value;
	}

	template <typename T>
	static T abs(T value)
	{
		return value < 0 ? -value : value;
	}

	/**
	 * @brief Change the velocity of an entity based on the player input
	 * @param velocity Current velocity of the entity
	 * @param acceleration Number of frames needed to reach max speed
	 * @param maxSpeed Maximum speed of the entity
	 * @param
	 */
	static void changeVelocity(
		ECS::components::VelocityComponent &velocity,
		ECS::components::ControllableComponent &controllable,
		float nbFrameToMaxSpeed,
		float nbFrameToStop,
		float maxSpeed
	)
	{
		const float acceleration = maxSpeed / nbFrameToMaxSpeed;
		const float deceleration = maxSpeed / nbFrameToStop;

		if (IsKeyDown(controllable.up)) {
			velocity.y -= 1 * acceleration;
		} else if (IsKeyDown(controllable.down)) {
			velocity.y += 1 * acceleration;
		} else {
			if (abs(velocity.y) < deceleration) {
				velocity.y = 0;
			} else {
				velocity.y += (velocity.y > 0 ? -1 : 1) * deceleration;
			}
		}
		if (IsKeyDown(controllable.left)) {
			velocity.x -= 1 * acceleration;
		} else if (IsKeyDown(controllable.right)) {
			velocity.x += 1 * acceleration;
		} else {
			if (abs(velocity.x) < deceleration) {
				velocity.x = 0;
			} else {
				velocity.x += (velocity.x > 0 ? -1 : 1) * deceleration;
			}
		}
		velocity.x = clamp(velocity.x, -maxSpeed, maxSpeed);
		velocity.y = clamp(velocity.y, -maxSpeed, maxSpeed);
	}

	static void handleShooting(
		ECS::containers::Registry &registry,
		ECS::components::ControllableComponent &controllable,
		ECS::components::PositionComponent &position)
	{
		if (IsKeyDown(controllable.fire)) {
			controllable.timeFireButtonHeld += GetFrameTime();
			return;
		}
		if (controllable.timeFireButtonHeld > 0) {
			u_char strength = clamp(
				static_cast<u_char>(controllable.timeFireButtonHeld / systems::timeNeededForWaveBeam * components::maxWaveBeamStrength),
				static_cast<u_char>(1),
				components::maxWaveBeamStrength
			);
			auto missileEntity = registry.spawnEntity();
			if (strength > 1) {
				registry.emplaceComponent<ECS::components::WaveBeamComponent>(
					missileEntity,
					position.x,
					position.y,
					static_cast<std::size_t>(strength * components::waveBeamBaseDamage),
					strength
				);
			} else {
				registry.emplaceComponent<ECS::components::MissileComponent>(
					missileEntity,
					position.x,
					position.y,
					static_cast<std::size_t>(strength * components::missileBaseDamage)
				);
			}
			controllable.timeFireButtonHeld = 0;
		}
	}

	void controller(
		ECS::containers::Registry &registry,
		ECS::containers::SparseArray<ECS::components::PositionComponent> &positions,
		ECS::containers::SparseArray<ECS::components::VelocityComponent> &velocities,
		ECS::containers::SparseArray<ECS::components::ControllableComponent> &controllables)
	{
		const float maxSpeed = 500;
		const float nbFrameToMaxSpeed = 5;
		const float nbFrameToStop = 5;

		for (auto &&[position, velocity, controllable] : ECS::containers::Zipper(positions, velocities, controllables)) {
			changeVelocity(*velocity, *controllable, nbFrameToMaxSpeed, nbFrameToStop, maxSpeed);
			handleShooting(registry, *controllable, *position);
		}
	}

}; // namespace ECS::systems
