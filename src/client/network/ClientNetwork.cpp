/*
** EPITECH PROJECT, 2023
** ClientNetwork.cpp
** File description:
** ClientNetwork
*/

#include "client/network/ClientNetwork.hpp"

Network::ClientNetwork::ClientNetwork(boost::asio::io_service &io_service, const std::string &host, int port) : _port(port), _host(host), _socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0))
{}

Network::ClientNetwork::~ClientNetwork()
{}

void Network::ClientNetwork::handleReceive(boost::system::error_code error, std::size_t recvd_bytes)
{
	if (!error && recvd_bytes > 0) {
		std::cout << "[" << recvd_bytes << "] " << _data << std::endl;
		receive(_socket);
	}
}

void Network::ClientNetwork::handleSend(boost::system::error_code error, std::size_t recvd_bytes)
{
	if (!error && recvd_bytes > 0) {
		std::cout << "[" << recvd_bytes << "] " << _data << std::endl;
		receive(_socket);
	}
}
