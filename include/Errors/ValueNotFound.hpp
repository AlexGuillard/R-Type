/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** ValueNotFound
*/

#pragma once

#include <stdexcept>

namespace Errors {

    class ValueNotFound : public std::runtime_error {
    public:
        explicit ValueNotFound(const std::string &what)
            : std::runtime_error(std::string("ValueNotFound: ") + what) {};
    };

}; // namespace Error
