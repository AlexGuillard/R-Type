/*
** EPITECH PROJECT, 2023
** ClientNetwork.cpp
** File description:
** ClientNetwork
*/

#include "client/network/ClientNetwork.hpp"

Network::ClientNetwork::ClientNetwork(int port, std::string machine) : _port(port), _host(machine), _fdClient(-1)
{
}

Network::ClientNetwork::~ClientNetwork()
{
	if (_fdClient == -1) {
		close(_fdClient);
	}
}

void Network::ClientNetwork::send(const std::string& message)
{
	if (_fdClient == -1) {
		throw Error("Error:client not connected");
	}

	if (::send(_fdClient, message.c_str(), message.size(), 0) == -1) {
		throw Error("Error: failed to send message");
	}
}
