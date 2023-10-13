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
#include "ECS/Containers/Registry.hpp"

namespace ECS {

    class Creator {
    public:
        Creator() = delete;
        ~Creator() = delete;

        /**
         * @brief Add a walking AI to an entity.
         * Assumes the entity already has a position, velocity and hitbox.
         *
         * @param entity Entity to add the AI to
         * @param registry Registry to add the AI to
         * @param target Target of the AI
         * @param preferredDistance Pair of floats representing the preferred
         * @param speed Walking speed of the entity
         * @param dropsDownLedge Whether the entity can drops down ledges
         * @param jumpsOverObstacle Whether the entity can jump over obstacles
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
         * @brief Create a base entity
         * @param registry The registry to create the entity in
         * @//param team The team the entity belongs to
         * @param damage The damage the entity deals to the other team on collision
         * @param health The health of the entity
         * @param width The width of the entity's hitbox/texture
         * @param height The height of the entity's hitbox/texture
         */
        static Entity createCharacter(
            Containers::Registry &registry,
            /* enum TeamGroup team, */
            std::size_t damage,
            std::size_t health,
            std::size_t width,
            std::size_t height
        );
        /**
         * @brief Create a base entity
         * @param registry The registry to create the entity in
         * @//param team The team the entity belongs to
         * @param damage The damage the entity deals to the other team on collision
         * @param health The health of the entity
         * @param width The width of the entity's hitbox/texture
         * @param height The height of the entity's hitbox/texture
         * @param id The id of the entity
         */
        static Entity createCharacter(
            Containers::Registry &registry,
            /* enum TeamGroup team, */
            std::size_t damage,
            std::size_t health,
            std::size_t width,
            std::size_t height,
            std::size_t id
        );

        static Entity createBydoShot(
            Containers::Registry &registry,
            float x,
            float y,
            float xDirection,
            float yDirection,
            Enums::TeamGroup team = Enums::TeamGroup::ENEMY
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
    protected:
    private:
    };

} // namespace ECS
