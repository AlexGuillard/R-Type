/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Creator
*/

#pragma once

#include <cstddef>

#include "enums.hpp"
#include "ECS/Entity.hpp"
#include "ECS/Creator.hpp"
#include "ECS/Containers/Registry.hpp"

namespace ECS {

    class Creator {
    public:
        static constexpr float defaultGravity = 9.81F;

        Creator() = delete;
        ~Creator() = delete;

        /**
         * @brief Set the global horizontal scroll speed
         * @param speed The speed to set in pixels per second
         */
        static void setLevelScrollSpeed(float speed);
        /**
         * @returns The global horizontal scroll speed in pixels per second
         */
        static float getLevelScrollSpeed();

        /**
         * @brief Add a walking AI to an entity.
         * Assumes the entity already has a position, velocity and hitbox.
         *
         * @param entity Entity to add the AI to
         * @param registry Registry to add the AI to
         * @param target Target of the AI
         * @param preferredDistance Pair of floats representing the preferred
         * @param speed Walking speed of the entity
         * @param dropsDownLedge Whether the entity can drops down ledges (not implemented yet)
         * @param jumpsOverObstacle Whether the entity can jump over obstacles (not implemented yet)
         * @return Entity The entity with the AI
         */
        static Entity addWalkingAI(
            const Entity &entity,
            Containers::Registry &registry,
            const Entity &target,
            std::pair<float, float> preferredDistance,
            float speed,
            bool dropsDownLedge = false,
            bool jumpsOverObstacle = false);

        /**
         * @brief Adds a bydo shooting AI to an entity.
         *
         * @param entity Entity to add the AI to
         * @param registry Registry the entity is in
         * @param target Target of the AI
         * @param shootCooldown Time between each shot in seconds
         * @param shotSpeed Speed of the shot in pixels per second
         * @return Entity The entity with the AI
         */
        static Entity addBydoShootingAI(
            const Entity &entity,
            Containers::Registry &registry,
            const Entity &target,
            float shootCooldown,
            float shotSpeed
        );

        /**
         * @brief Create a base entity
         * @param registry The registry to create the entity in
         * @param team The team the entity belongs to
         * @param damage The damage the entity deals to the other team on collision
         * @param health The health of the entity
         * @param width The width of the entity's hitbox/texture
         * @param height The height of the entity's hitbox/texture
         */
        static Entity createCharacter(
            Containers::Registry &registry,
            enum Enums::TeamGroup team,
            std::size_t damage,
            std::size_t health,
            std::size_t width,
            std::size_t height
        );
        /**
         * @brief create a base missile
         *
         * @param registry The registry to create the entity in
         * @param id id of entity
         * @param x position X
         * @param y position y
         * @param team team of the missile
         * @return Entity
         */
        static Entity createMissile(Containers::Registry &registry, size_t id, int x, int y, Enums::TeamGroup team);
        /**
         * @brief create a base wave beam
         *
         * @param registry The registry to create the entity in
         * @param id id of entity
         * @param x position X
         * @param y position y
         * @param team team of the wave beam
         * @return Entity
         */
        static Entity createWaveBeam(Containers::Registry &registry, size_t id, int x, int y, Enums::TeamGroup team);
        /**
         * @brief Create a base entity
         * @param registry The registry to create the entity in
         * @param team The team the entity belongs to
         * @param damage The damage the entity deals to the other team on collision
         * @param health The health of the entity
         * @param width The width of the entity's hitbox/texture
         * @param height The height of the entity's hitbox/texture
         * @param id The id of the entity
         */
        static Entity createCharacter(
            Containers::Registry &registry,
            enum Enums::TeamGroup team,
            std::size_t damage,
            std::size_t health,
            std::size_t width,
            std::size_t height,
            std::size_t id
        );

        /**
         * @brief Create a bydo shot
         *
         * @param registry The registry to create the entity in
         * @param x The x position of the entity
         * @param y The y position of the entity
         * @param xDirection The x direction of the entity
         * @param yDirection The y direction of the entity
         * @param team The team the entity belongs to
         * @return Entity The entity created
         */
        static Entity createBydoShot(
            Containers::Registry &registry,
            float x,
            float y,
            float xDirection,
            float yDirection,
            Enums::TeamGroup team = Enums::TeamGroup::ENEMY
        );

        /**
         * @brief Create a base entity that moves with the background
         *
         * @param registry The registry to create the entity in
         * @param team The team the entity belongs to
         * @param damage The damage the entity deals to the other team on collision
         * @param health The health of the entity
         * @param width The width of the entity's hitbox/texture
         * @param height The height of the entity's hitbox/texture
         * @param id The id of the entity
         */
        static Entity createGroundedCharacter(
            Containers::Registry &registry,
            enum Enums::TeamGroup team,
            std::size_t damage,
            std::size_t health,
            std::size_t width,
            std::size_t height,
            std::size_t id
        );

        /**
         * @brief Create a Enemy Basic object
         *
         * @param registry registre entity
         * @param id id of entity
         * @param x position X
         * @param y position y
         */
        static Entity createEnemyBasic(Containers::Registry &registry, size_t id, int x, int y);
        /**
         * @brief Create a Enemy Bink object
         *
         * @param registry registre entity
         * @param id id of entity
         * @param x position X
         * @param y position y
         */
        static Entity createBink(Containers::Registry &registry, size_t id, int x, int y);
        /**
         * @brief Create a Enemy Scant object
         *
         * @param registry registre entity
         * @param id id of entity
         * @param x position X
         * @param y position y
         */
        static Entity createScant(Containers::Registry &registry, size_t id, int x, int y);
        /**
         * @brief Create a Enemy Bug object
         *
         * @param registry registre entity
         * @param id id of entity
         * @param x position X
         * @param y position y
         */
        static Entity createBug(Containers::Registry &registry, size_t id, int x, int y);
        /**
         * @brief Create a enemy Cancer object
         *
         * @param registry registre entity
         * @param id id of entity
         * @param x position X
         * @param y position y
         */
        static Entity createCancer(Containers::Registry &registry, size_t id, int x, int y);
        /**
         * @brief Create a Blaster object
         *
         * @param registry registre entity
         * @param id id of entity
         * @param x position X
         * @param y position y
         */
        static Entity createBlaster(Containers::Registry &registry, size_t id, int x, int y);
        /**
         * @brief Create a Ally object
         *
         * @param registry registre entity
         * @param id id of entity
         * @param x position X
         * @param y position y
         * @param color color of the ship
         */
        static Entity createAlly(Containers::Registry &registry, size_t id, int x, int y, Enums::PlayerColor color);
        /**
         * @brief Create a Player object
         *
         * @param registry registre entity
         * @param id id of entity
         * @param x position X
         * @param y position y
         * @param color color of the ship
         */
        static Entity createPlayer(Containers::Registry &registry, size_t id, int x, int y, Enums::PlayerColor color);
        /**
         * @brief Create a Dobkeratops object
         *
         * @param registry registre entity
         * @param id id of entity
         * @param x position X
         * @param y position y
         */
        static Entity createDobkeratops(Containers::Registry &registry, size_t id, int x, int y);
    private:
        static float mLevelScrollSpeed;
    };

} // namespace ECS
