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

    initializeResponsehandler();
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
    if (error && recvd_bytes == 0) {
        return;
    }
    _dataReceived.resize(recvd_bytes);
    std::copy(_data.begin(), _data.begin() + recvd_bytes, _dataReceived.begin());

    std::string receivedMessage(_dataReceived.begin(), _dataReceived.end());

    enqueueReceivedMessage(receivedMessage);

    std::cout << "Received: " << receivedMessage << std::endl;

    auto responseHandlerIt = _responseHandlers.find(receivedMessage);

    if (responseHandlerIt != _responseHandlers.end()) {
        responseHandlerIt->second(receivedMessage);
    }
}

void Network::ClientNetwork::handleSend(boost::system::error_code error, std::size_t recvd_bytes)
{
    if (!error && recvd_bytes > 0) {
        std::cout << "[" << recvd_bytes << "] " << _data.data() << std::endl;
        asyncReceive(_socket);
    } else {
        std::cout << "erreur\n";
    }
}

void Network::ClientNetwork::sendHello()
{
    asyncSend(_socket, "Hello R-Type server\n");
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
    asyncSend(_socket, message);
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
    asyncSend(_socket, message);
}

bool Network::ClientNetwork::connect(const std::string &host, int port)
{
    try {
        boost::asio::ip::udp::endpoint serverEndpoint(boost::asio::ip::address::from_string(host), port);
        _endpoint = serverEndpoint;
        _socket.open(_endpoint.protocol());
        sendHello();
    }

    catch (std::exception &e) {
    	std::cerr << "Error connecting to server: " <<e.what() << std::endl;
        return (false);
    }

    return (true);
}

void Network::ClientNetwork::initializeResponsehandler()
{
    _responseHandlers["200\n"] = std::bind(&ClientNetwork::handleConnection, this, std::placeholders::_1);
    _responseHandlers["201\n"] = std::bind(&ClientNetwork::handleLogin, this, std::placeholders::_1);
    _responseHandlers["202\n"] = std::bind(&ClientNetwork::handleLogout, this, std::placeholders::_1);
}

void Network::ClientNetwork::handleConnection(const std::string &message)
{
    if (message == "200\n") {
        std::cout << "Ur connected" << std::endl;
    } else {
        std::cout << "Unexecepted message received" << std::endl;
    }
}

void Network::ClientNetwork::handleLogin(const std::string &message)
{
    if (message == "201\n") {
        std::cout << "Ur logged" << std::endl;
    } else {
        std::cout << "Unexecepted message received" << std::endl;
    }
}

void Network::ClientNetwork::handleLogout(const std::string &message)
{
    if (message == "202\n") {
        std::cout << "Ur loggout" << std::endl;
    } else {
        std::cout << "Unexecepted message received" << std::endl;
    }
}

std::unique_ptr<Network::ClientNetwork> Network::ClientNetwork::_instance = std::unique_ptr<Network::ClientNetwork>();

Network::ClientNetwork &Network::ClientNetwork::getInstance()
{
    if (_instance == nullptr) {
        _instance.reset(new ClientNetwork());
    }
    return *_instance;
}

Network::ClientNetwork &Network::ClientNetwork::getInstance(boost::asio::io_service &io_service, const std::string &host, int port)
{
    if (_instance == nullptr) {
        _instance.reset(new ClientNetwork(io_service, host, port));
    }
    return *_instance;
}

void Network::ClientNetwork::enqueueReceivedMessage(const std::string& message) {
    _receivedMessages.push(message);
}

void Network::ClientNetwork::handleNetwork()
{
    _ioService.reset();
    _ioService.poll();
}

void Network::ClientNetwork::stopIOService() {
    _ioService.stop();
}

boost::asio::ip::udp::socket& Network::ClientNetwork::getSocket() {
    return _socket;
}
