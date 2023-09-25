/*
** EPITECH PROJECT, 2023
** ServerNetwork.cpp
** File description:
** ServerNetwork
*/

#include "server/network/ServerNetwork.hpp"

Network::ServerNetwork::ServerNetwork(std::string hostname, int port) : _socket(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
{
}

Network::ServerNetwork::~ServerNetwork()
{
}
