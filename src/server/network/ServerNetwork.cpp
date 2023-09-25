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

void Network::ServerNetwork::receive()
{
	_socket.async_receive_from(asio::buffer(_data, 1024), _endpoint, handle);
	std::cout << _data << std::endl;
}

void Network::ServerNetwork::handle(const asio::error_code& error, std::size_t bytes_transferred)
{
    std::cout << "Received: '" << bytes_transferred << "bytes from server" << "'\n";
}
