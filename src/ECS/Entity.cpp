/*
** EPITECH PROJECT, 2023
** Entity.cpp
** File description:
** Entity
*/

#include <limits>

#include "ECS/Entity.hpp"

ECS::Entity::Entity(std::size_t entity) : _entity(entity) {}

ECS::Entity::operator std::size_t() const
{
    return this->_entity;
}

ECS::NullEntity::NullEntity() : Entity(std::numeric_limits<std::size_t>::max()) {}
