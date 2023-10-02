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
    initializeResponsehandler();
}

Network::ClientNetwork::~ClientNetwork()
{}

void Network::ClientNetwork::handleReceive(boost::system::error_code error, std::size_t recvd_bytes)
{
    if (!error && recvd_bytes > 0) {
        _dataReceived.resize(recvd_bytes);
        std::copy(_buffer.begin(), _buffer.begin() + recvd_bytes, _dataReceived.begin());
        std::cout << "[" << recvd_bytes << "] " << _dataReceived << std::endl;

        auto responseHandlerIt = _responseHandlers.find(_dataReceived);
        if (responseHandlerIt != _responseHandlers.end()) {
            responseHandlerIt->second(_dataReceived);
        }
    } else {
	    receive(_socket);
	}
}

void Network::ClientNetwork::handleSend(boost::system::error_code error, std::size_t recvd_bytes)
{
	if (!error && recvd_bytes > 0) {
		std::cout << "[" << recvd_bytes << "] " << _data.data() << std::endl;
		receive(_socket);
	}
}

void Network::ClientNetwork::sendHello()
{
	send(_socket, "Hello R-Type server\r");
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

void Network::ClientNetwork::initializeResponsehandler()
{
    _responseHandlers["pong"] = std::bind(&ClientNetwork::handlePong, this, std::placeholders::_1);
    _responseHandlers["200"] = std::bind(&ClientNetwork::handleConnection, this, std::placeholders::_1);
    _responseHandlers["201"] = std::bind(&ClientNetwork::handleLogin, this, std::placeholders::_1);
    _responseHandlers["202"] = std::bind(&ClientNetwork::handleLogout, this, std::placeholders::_1);
}

void Network::ClientNetwork::handlePong(const std::string &message)
{
    if (message == "ping") {
        send(_socket, "pong");
    } else {
        std::cout << "Unexecepted message received" << std::endl;
    }
}

void Network::ClientNetwork::handleConnection(const std::string &message)
{
    if (message == "200") {
        std::cout << "Ur connected" << std::endl;
    } else {
        std::cout << "Unexecepted message received" << std::endl;
    }
}

void Network::ClientNetwork::handleLogin(const std::string &message)
{
    if (message == "201") {
        std::cout << "Ur logged" << std::endl;
    } else {
        std::cout << "Unexecepted message received" << std::endl;
    }
}

void Network::ClientNetwork::handleLogout(const std::string &message)
{
    if (message == "202") {
        std::cout << "Ur loggout" << std::endl;
    } else {
        std::cout << "Unexecepted message received" << std::endl;
    }
}
