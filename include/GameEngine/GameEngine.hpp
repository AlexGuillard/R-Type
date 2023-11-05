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
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Components/LevelComponent.hpp"
#include "ECS/Components/TeamComponent.hpp"
#include "ECS/Components/WaveBeamComponent.hpp"

namespace GameEngine {
    // Registry type
    const std::string registryTypeEntities = "Entities";
    const std::string registryTypeBackground = "Background";

    typedef std::function<void(ECS::Containers::Registry &registry,
        ECS::Containers::SparseArray<ECS::Components::PositionComponent> &positions,
        ECS::Containers::SparseArray<ECS::Components::VelocityComponent> &velocities,
        ECS::Containers::SparseArray<ECS::Components::TeamComponent> &teams,
        ECS::Containers::SparseArray<ECS::Components::WaveBeamComponent> &waveBeams
        )> ServerEventHandler;

    class GameEngine {
        using Registry = ECS::Containers::Registry;
    public:
        GameEngine() = default;
        ~GameEngine() = default;

        Registry &operator[](const std::string &type);
        const Registry &operator[](const std::string &type) const;

        /**
         * @brief Kills all the entities that are not immortal and not reserved
         * in the registries
        */
        void reset();
        /**
         * @brief Kills all the entities that are not immortal and not reserved
         * in the specified registry
         * @param type Registry type
        */
        void reset(const std::string &type);
        /**
         * @brief Creates a registry of the given type
         * @param type type of the registry
         * @return The registry
        */
        Registry &createRegistry(const std::string &type);
        /**
         * @brief Creates a registry of the given type
         * @param type type of the registry
         * @param reservedIds number of ids to reserve
         * @return The registry
        */
        Registry &createRegistry(const std::string &type, std::size_t reservedIds);

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
        /**
         * @brief set the levels of background registry to the current level
         */
        void changeStageRegistryBkgr(ECS::Containers::SparseArray<ECS::Components::LevelComponent> &levels) const;
        /**
         * @brief set the level of the game
         */
        void setLevel(int level);
        /**
          * @brief Returns the current level of the game
         * @return The level in int
         */
        int getLevel() const;
        /**
         * @brief Returns the delta time between the last two calls to run
         * @return The delta time
         */
        static double getDeltaTime();
        //add list id of boss
        std::vector<ECS::Entity> _listIdBoss;
    private:
        // Registry type and registry sorted by insertion order
        std::vector<std::pair<std::string, Registry>> m_registries;
        int _level = 1;
        static double mDeltaTime;
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
    GameEngine createServerEngine(ServerEventHandler serverEventHandler);
}; // namespace ECS::GameEngine
