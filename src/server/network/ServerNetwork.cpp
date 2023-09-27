/*
** EPITECH PROJECT, 2023
** ServerNetwork.cpp
** File description:
** ServerNetwork
*/

#include "server/network/ServerNetwork.hpp"

Network::ServerNetwork::ServerNetwork(boost::asio::io_service& io_service, int port)
	: _socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
{
	receive(_socket);
}

Network::ServerNetwork::~ServerNetwork()
{
}

void Network::ServerNetwork::handleReceive(boost::system::error_code error, std::size_t recvd_bytes)
{
	std::string actualClient;

    if ( !error && recvd_bytes > 0 ) {
		std::cout << clients.size() << std::endl;
		if (clients.size() < 5) {
			actualClient = _endpoint.address().to_string() + ":" + std::to_string(_endpoint.port());
			clients[actualClient] = _endpoint;
		}
        std::cout << "[" << recvd_bytes << "] " << _data << std::endl;
        send(_socket, "receive data\n");
		for (int i = 0; i < MAX_SIZE_BUFF; i++) {
			_data[i] = '\0';
		}
    }
    else {
        receive(_socket);
    }
}

void Network::ServerNetwork::handleSend(boost::system::error_code error, std::size_t recvd_bytes)
{
	receive(_socket);
}
