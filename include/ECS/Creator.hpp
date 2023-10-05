/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Creator
*/

#pragma once

#include <cstddef>

#include "ECS/Entity.hpp"
#include "ECS/Containers/Registry.hpp"
#include <raylib.h>

namespace ECS {

    class Creator {
    public:
        Creator() = delete;
        ~Creator() = delete;

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
        /**
         * @brief Create a Enemy Basic object
         *
         * @param registry
         * @param id
         * @param x
         * @param y
         */
        static void createEnemyBasic(Containers::Registry &registry, size_t id, int x, int y);
    protected:
    private:
    };

} // namespace ECS
