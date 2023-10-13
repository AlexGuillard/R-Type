/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** GameEngine
*/

#pragma once

#include <string>
#include <vector>
#include <utility> // std::pair

#include "ECS/Containers/Registry.hpp"

namespace GameEngine {
    // Registry type
    const std::string registryTypeEntities = "Entities";
    const std::string registryTypeBackground = "Background";

    class GameEngine {
        using Registry = ECS::Containers::Registry;
    public:
        GameEngine() = default;
        ~GameEngine() = default;

        Registry &operator[](const std::string &type);
        const Registry &operator[](const std::string &type) const;

        Registry &createRegistry(const std::string &type);

        /**
         * @brief Returns the registry of the given type
         * @param type The type of the registry
         * @return The registry
         */
        Registry &getRegistry(const std::string &type);

        /**
         * @brief Returns the registry of the given type
         * @param type The type of the registry
         * @return The registry
         */
        const Registry &getRegistry(const std::string &type) const;

        /**
         * @brief Runs the game engine by running the systems.
         * It will do that by running the registries in the order they were
         * inserted.
         */
        void run();

    private:
        // Registry type and registry sorted by insertion order
        std::vector<std::pair<std::string, Registry>> m_registries;
    };

    /**
     * @brief Creates a game engine that can run the game
     */
    GameEngine createEngine();
    /**
     * @brief Create the game engine that will run the game on the client side
     */
    GameEngine createClientEngine();
    /**
     * @brief Create the game engine that will run the game on the server side
     */
    GameEngine createServerEngine();
}; // namespace ECS::GameEngine
