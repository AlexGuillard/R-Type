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

Network::ClientNetwork::ClientNetwork() : _port(0), _socket(_ioService)
{
}

Network::ClientNetwork::~ClientNetwork()
{}

void Network::ClientNetwork::handleReceive(boost::system::error_code error, std::size_t recvd_bytes)
{
    if (!error && recvd_bytes > 0) {
        _dataReceived.resize(recvd_bytes);
        std::copy(_buffer.begin(), _buffer.begin() + recvd_bytes, _dataReceived.begin());
        std::cout << "[" << recvd_bytes << "] " << _dataReceived << std::endl;
    } else {
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
	send(_socket, "Hello R-Type server\r");
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

bool Network::ClientNetwork::connect(const std::string &host, int port)
{
	try {
	    boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string(host), port);
	    _endpoint = endpoint;
	    _socket.open(endpoint.protocol());

	    sendHello();

        receive(_socket);
        std::string receive = _data;
        if (receive == "200") {
			std::cout << "Connected to server" << std::endl;
			return (true);
        }
	}

	catch (std::exception &e) {
		std::cerr << "Error connecting to server: " <<e.what() << std::endl;
	}

	return (false);
}
