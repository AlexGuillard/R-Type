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
#include "ECS/Components/WaveBeamComponent.hpp"
#include "ECS/Components/MissileComponent.hpp"
#include "ECS/Containers/zipper/Zipper.hpp"
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
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;

        if (IsKeyDown(controllable.up)) {
            GameEngine::Events::push(GameEngine::Events::Type::PLAYER_UP);
            up = true;
        } else if (IsKeyDown(controllable.down)) {
            GameEngine::Events::push(GameEngine::Events::Type::PLAYER_DOWN);
            down = true;
        }
        if (IsKeyDown(controllable.left)) {
            GameEngine::Events::push(GameEngine::Events::Type::PLAYER_LEFT);
            left = true;
        } else if (IsKeyDown(controllable.right)) {
            GameEngine::Events::push(GameEngine::Events::Type::PLAYER_RIGHT);
            right = true;
        }
        Player::movePlayer(velocity.x, velocity.y, up, down, left, right);
    }

    static void handleShooting(
        ECS::Containers::Registry &registry,
        ECS::Components::ControllableComponent &controllable,
        ECS::Components::PositionComponent &position)
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
                    static_cast<std::size_t>(strength * Components::waveBeamBaseDamage),
                    strength
                );
            } else {
                registry.emplaceComponent<ECS::Components::MissileComponent>(
                    missileEntity,
                    position.x,
                    position.y,
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
        ECS::Containers::SparseArray<ECS::Components::ControllableComponent> &controllables)
    {
        for (auto &&[position, velocity, controllable] : ECS::Containers::Zipper(positions, velocities, controllables)) {
            changeVelocity(*velocity, *controllable);
            handleShooting(registry, *controllable, *position);
            useForce(registry, *controllable);
        }
    }

}; // namespace ECS::Systems
