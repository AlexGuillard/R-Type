/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** network
*/

#pragma once

#include <string>
#include "GameEngine/GameEngine.hpp"

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
    bool startClientNetwork(const std::string &host, int tcpPort, int udpPort, Network::ConnectionType type, GameEngine::GameEngine &engine);
    /**
     * @brief Update the client.
     * Fetches the server information then answers from the server
     */
    void updateClientNetworkUDP();
    /**
     * @brief Update the TCP client.
     * Fetches the server information then answers from the server
     */
    void updateClientNetworkTCP(bool playButton);
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
    /**
     * @brief Get the Winning Condition object
     *
     * @return true won
     * @return false
     */
    bool getWinningCondition();
    /**
     * @brief Get the Loosing Condition object
     *
     * @return true lose
     * @return false
     */
    bool getLoosingCondition();
} // namespace Network
