/*
** EPITECH PROJECT, 2023
** Entity.hpp
** File description:
** Entity
*/

#pragma once

#include <cstddef>

namespace ECS {
    namespace Containers {
        class Registry;
    }
    class Entity {
    public:
        operator std::size_t() const;

    private:
        friend class Containers::Registry;
        friend class NullEntity;
        explicit Entity(std::size_t entity);
        std::size_t _entity;
    };

    /**
     * @brief NullEntity is an entity that is not valid.
     */
    class NullEntity : public Entity {
    public:
        NullEntity();
    };
}
