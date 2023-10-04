/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** controller
*/

#include <raylib.h>

#include "ECS/Systems/controller.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Components/ControllableComponent.hpp"
#include "ECS/Components/WaveBeamComponent.hpp"
#include "ECS/Components/MissileComponent.hpp"
#include "ECS/Containers/zipper/Zipper.hpp"
#include "GameEngine/Events.hpp"

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
        ECS::Components::VelocityComponent &velocity,
        ECS::Components::ControllableComponent &controllable,
        float nbFrameToMaxSpeed,
        float nbFrameToStop,
        float maxSpeed
    )
    {
        const float acceleration = maxSpeed / nbFrameToMaxSpeed;
        const float deceleration = maxSpeed / nbFrameToStop;
        if (IsKeyDown(controllable.up)) {
            GameEngine::Events::push(GameEngine::Events::Type::PLAYER_UP);
            velocity.y -= 1 * acceleration;
        } else if (IsKeyDown(controllable.down)) {
            GameEngine::Events::push(GameEngine::Events::Type::PLAYER_DOWN);
            velocity.y += 1 * acceleration;
        } else {
            if (abs(velocity.y) < deceleration) {
                velocity.y = 0;
            } else {
                velocity.y += (velocity.y > 0 ? -1 : 1) * deceleration;
            }
        }
        if (IsKeyDown(controllable.left)) {
            GameEngine::Events::push(GameEngine::Events::Type::PLAYER_LEFT);
            velocity.x -= 1 * acceleration;
        } else if (IsKeyDown(controllable.right)) {
            GameEngine::Events::push(GameEngine::Events::Type::PLAYER_RIGHT);
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
        const float maxSpeed = 500;
        const float nbFrameToMaxSpeed = 5;
        const float nbFrameToStop = 5;

        for (auto &&[position, velocity, controllable] : ECS::Containers::Zipper(positions, velocities, controllables)) {
            changeVelocity(*velocity, *controllable, nbFrameToMaxSpeed, nbFrameToStop, maxSpeed);
            handleShooting(registry, *controllable, *position);
            useForce(registry, *controllable);
        }
    }

}; // namespace ECS::Systems
