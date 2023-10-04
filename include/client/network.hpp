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
     * @brief Start running the client
     * @returns True if the client successfully started, false otherwise
     */
    bool startClientNetwork(const std::string &host, int port);
    /**
     * @brief Update the client.
     * Fetches the server information then answers from the server
     */
    void updateClientNetwork();
    /**
     * @brief Cleanup the client
     */
    void stopClientNetwork();
} // namespace Network
