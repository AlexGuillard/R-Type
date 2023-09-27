/*
** EPITECH PROJECT, 2023
** ClientNetwork.cpp
** File description:
** ClientNetwork
*/

#include "client/network/ClientNetwork.hpp"

Network::ClientNetwork::ClientNetwork(boost::asio::io_service &io_service, const std::string &host, int port) : _port(port), _host(host), _socket(io_service)
{
    boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string(host), port);
    _endpoint = endpoint;
    _socket.open(endpoint.protocol());

    sendHello();
}

Network::ClientNetwork::~ClientNetwork()
{}

void Network::ClientNetwork::handleReceive(boost::system::error_code error, std::size_t recvd_bytes)
{
    if (!error && recvd_bytes > 0) {
        std::array<char, 1024> buffer;
        std::copy(_data.begin(), _data.begin() + recvd_bytes, buffer.begin());
        _data = std::string(buffer.begin(), buffer.begin() + recvd_bytes);
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

void Network::ClientNetwork::sendHello()
{
	send(_socket, "Hello");
	std::cout << "Hello sent" << std::endl;
}

void Network::ClientNetwork::start()
{
	receive(_socket);
}

void Network::ClientNetwork::sendMovement(Movement movement)
{
	std::string message;

	switch (movement) {
		case Movement::UP:
			message = "211";
			break;
		case Movement::DOWN:
			message = "212";
			break;
		case Movement::LEFT:
			message = "213";
			break;
		case Movement::RIGHT:
			message = "214";
			break;
		default:
			break;
	}
	send(_socket, message);
}

void Network::ClientNetwork::sendAction(Action action)
{
	std::string message;

	switch (action) {
		case Action::SHOOT:
			message = "215";
			break;
		case Action::DROP:
			message = "216";
			break;
		default:
			break;
	}
	send(_socket, message);
}
