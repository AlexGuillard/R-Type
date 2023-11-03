/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** network
*/

#pragma once

#include <string>
#include "GameEngine/GameEngine.hpp"
#include "enums.hpp"

namespace Network {
    /**
     * @brief enum use to know how to connect to the server
     *
     */
    enum class ConnectionType {
        TCP,
        UDP
    };
    static bool isCoUDP = false;
    bool returnIsCoUDP();
    /**
     * @brief Start running the client
     * @returns True if the client successfully started, false otherwise
     */
    bool startClientNetwork(const std::string &host, int port, Network::ConnectionType type, Enums::MultiState multi, Enums::ModeSelect mode, GameEngine::GameEngine &engine);
    /**
     * @brief Update the client.
     * Fetches the server information then answers from the server
     */
    void updateClientNetworkUDP();
    /**
     * @brief Check if the client has a 401 error
     *
     * @return true if the client has a 401 error
     * @return false
     */
    bool check401Error();
    /**
     * @brief Update the TCP client.
     * Fetches the server information then answers from the server
     */
    void updateClientNetworkTCP(bool playButton, Enums::ModeSelect mode);
    /**
     * @brief Cleanup the client
     */
    void stopClientNetwork();
    /**
     * @brief Set the Engine To Network object
     *
     * @param engine
     */
    void setEngineToNetwork(GameEngine::GameEngine &engine);
} // namespace Network
