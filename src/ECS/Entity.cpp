/*
** EPITECH PROJECT, 2023
** Entity.cpp
** File description:
** Entity
*/

#include "Entity.hpp"

Entity::Entity(std::size_t entity) : _entity(entity)
{

}

Entity::operator std::size_t() const
{
    return this->_entity;
}
