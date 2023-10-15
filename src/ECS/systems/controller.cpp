/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** controller
*/

#include <raylib.h>
#include <cstdint>

#include "ECS/Systems/controller.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Components/ControllableComponent.hpp"
#include "ECS/Components/TeamComponent.hpp"
#include "ECS/Components/WaveBeamComponent.hpp"
#include "ECS/Components/MissileComponent.hpp"
#include "ECS/Containers/zipper/IndexedZipper.hpp"
#include "GameEngine/Events.hpp"
#include "constants.hpp"
#include "Player/utils.hpp"

namespace ECS::Systems {

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

    /**
     * @brief Change the velocity of an entity based on the player input
     * @param velocity Current velocity of the entity
     * @param acceleration Number of frames needed to reach max speed
     * @param maxSpeed Maximum speed of the entity
     * @param
     */
    static void changeVelocity(
        ECS::Components::VelocityComponent &velocity,
        ECS::Components::ControllableComponent &controllable
    )
    {
        std::size_t up = 0;
        std::size_t down = 0;
        std::size_t left = 0;
        std::size_t right = 0;

        if (IsKeyDown(controllable.up)) {
            GameEngine::Events::push(GameEngine::Events::Type::PLAYER_UP);
            up = 1;
        } else if (IsKeyDown(controllable.down)) {
            GameEngine::Events::push(GameEngine::Events::Type::PLAYER_DOWN);
            down = 1;
        }
        if (IsKeyDown(controllable.left)) {
            GameEngine::Events::push(GameEngine::Events::Type::PLAYER_LEFT);
            left = 1;
        } else if (IsKeyDown(controllable.right)) {
            GameEngine::Events::push(GameEngine::Events::Type::PLAYER_RIGHT);
            right = 1;
        }
        Player::updateVelocity(velocity.x, velocity.y, up, down, left, right);
    }

    static void handleShooting(
        ECS::Containers::Registry &registry,
        ECS::Components::ControllableComponent &controllable,
        ECS::Components::PositionComponent &position,
        ECS::Components::TeamComponent &team)
    {
        if (IsKeyDown(controllable.fire)) {
            GameEngine::Events::push(GameEngine::Events::Type::PLAYER_SHOOT);
            controllable.timeFireButtonHeld += GetFrameTime();
            return;
        }
        if (controllable.timeFireButtonHeld > 0) {
            uint8_t strength = clamp(
                static_cast<uint8_t>(controllable.timeFireButtonHeld / Systems::timeNeededForWaveBeam * Components::maxWaveBeamStrength),
                static_cast<uint8_t>(1),
                Components::maxWaveBeamStrength
            );
            auto missileEntity = registry.spawnEntity();
            if (strength > 1) {
                registry.emplaceComponent<ECS::Components::WaveBeamComponent>(
                    missileEntity,
                    position.x,
                    position.y,
                    team,
                    static_cast<std::size_t>(strength * Components::waveBeamBaseDamage),
                    strength
                );
            } else {
                registry.emplaceComponent<ECS::Components::MissileComponent>(
                    missileEntity,
                    position.x,
                    position.y,
                    team,
                    static_cast<std::size_t>(strength * Components::missileBaseDamage)
                );
            }
            controllable.timeFireButtonHeld = 0;
        }
    }

    /**
     * @brief If a Force is attached release it, otherwise, try to attach one
     * @param registry Registry in which the force and the controllable are stored
     * @param controllable Controllable component of the entity
     */
    static void useForce(
        ECS::Containers::Registry &registry,
        ECS::Components::ControllableComponent &controllable)
    {
        if (!IsKeyPressed(controllable.force)) { return; }
        GameEngine::Events::push(GameEngine::Events::Type::PLAYER_FORCE);
        // TODO: add force implementation here
    }


    void controller(
        ECS::Containers::Registry &registry,
        ECS::Containers::SparseArray<ECS::Components::PositionComponent> &positions,
        ECS::Containers::SparseArray<ECS::Components::VelocityComponent> &velocities,
        ECS::Containers::SparseArray<ECS::Components::TeamComponent> &teams,
        ECS::Containers::SparseArray<ECS::Components::ControllableComponent> &controllables)
    {
        for (auto &&[eId, position, velocity, controllable] : ECS::Containers::IndexedZipper(positions, velocities, controllables)) {
            auto &&team = teams.at(eId) ? *teams.at(eId) : ECS::Components::TeamComponent(Enums::TeamGroup::NEUTRAL);
            changeVelocity(*velocity, *controllable);
            handleShooting(registry, *controllable, *position, team);
            useForce(registry, *controllable);
        }
    }

}; // namespace ECS::Systems
