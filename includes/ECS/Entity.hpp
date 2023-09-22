/*
** EPITECH PROJECT, 2023
** Entity.hpp
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
    #define ENTITY_HPP_
    #include <iostream>
    #include <any>

class Entity {
    public:
        operator std::size_t() const;
    protected:
        friend class Registry;
        explicit Entity(std::size_t entity);
        std::size_t _entity;
    private:
};

#endif /* !ENTITY_HPP_ */
