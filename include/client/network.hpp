/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** network
*/

#pragma once

#include <string>

namespace Network {
    /**
     * @brief enum use to know how to connect to the server
     *
     */
    enum class ConnectionType {
        TCP,
        UDP
    };
    /**
     * @brief Start running the client
     * @returns True if the client successfully started, false otherwise
     */
    bool startClientNetwork(const std::string &host, int tcpPort, int udpPort, Network::ConnectionType type);
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
} // namespace Network
