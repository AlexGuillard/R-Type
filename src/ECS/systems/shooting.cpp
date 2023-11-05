/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** shooting
*/

#include "ECS/Containers/zipper/IndexedZipper.hpp"
#include "ECS/Components/MissileComponent.hpp"
#include "ECS/Systems/shooting.hpp"
#include "GameEngine/Events.hpp"
#include "GameEngine/GameEngine.hpp"

namespace ECS::Systems {

	template <typename T>
	static T max(T a, T b)
	{
		return a > b ? a : b;
	}

	void shooting(
		Containers::Registry &registry,
		Containers::SparseArray<Components::ShootingTimerComponent> &shootingTimers,
		Containers::SparseArray<Components::PositionComponent> &positions
    )
    {
		for (auto &&[entity, timer, position] : ECS::Containers::IndexedZipper(shootingTimers, positions)) {
			timer->_shootCooldownTimer = max<float>(0.F, timer->_shootCooldownTimer - GameEngine::GameEngine::getDeltaTime());
			if (timer->_shootCooldownTimer > 0) { continue; }
            timer->_shootCooldownTimer = timer->shootCooldown;
			switch (timer->shotType) {
			case Enums::ShotType::BASIC:
				registry.emplaceComponent<ECS::Components::MissileComponent>(registry.entityFromIndex(entity), position->x, position->y);
				GameEngine::Events::push(GameEngine::Events::Type::POD_SHOOT, entity);
                break;
			default:
                break;
			}
		}
    }
}; // namespace ECS::Systems
