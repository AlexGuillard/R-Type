/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** RegistryNotFound
*/

#pragma once

#include <stdexcept>

namespace Errors {
    class RegistryNotFound : public std::runtime_error {
    public:
        RegistryNotFound(const std::string &type)
            : std::runtime_error("Registry not found: " + type)
        {}
    };
}; // namespace Errors
