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
    std::cout << "ClientNetwork constructor" << std::endl;
    _senderEndpoint = boost::asio::ip::udp::endpoint(
        boost::asio::ip::address::from_string("127.0.0.1"), 4848);
}

Network::ClientNetwork::~ClientNetwork()
{}

void Network::ClientNetwork::handleReceive(boost::system::error_code error, std::size_t recvd_bytes)
{
    if (error && recvd_bytes == 0) {
        return;
    }
    _dataReceived.resize(recvd_bytes);
    std::copy(_buffer.begin(), _buffer.begin() + recvd_bytes, _dataReceived.begin());

    std::string receivedMessage(_dataReceived.begin(), _dataReceived.end());

    enqueueReceivedMessage(receivedMessage);

    auto responseHandlerIt = _responseHandlers.find(receivedMessage);

    if (responseHandlerIt != _responseHandlers.end()) {
        responseHandlerIt->second(receivedMessage);
    }

    std::cout << "Received: " << receivedMessage << std::endl;
}


void Network::ClientNetwork::handleSend(boost::system::error_code error, std::size_t recvd_bytes)
{
    if (!error && recvd_bytes > 0) {
        std::cout << "[" << recvd_bytes << "] " << _data.data() << std::endl;
        myReceive();
    } else {
        std::cout << "erreur\n";
    }
}

void Network::ClientNetwork::sendHello()
{
    // send(_socket, "Hello R-Type server\n");
    mySend("Hello R-Type server\n");
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
    // send(_socket, message);
    mySend(message);
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
    // send(_socket, message);
    mySend(message);
}

bool Network::ClientNetwork::connect(const std::string &host, int port)
{
    // try {
        // boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string(host), port);
    boost::asio::ip::udp::endpoint serverEndpoint(boost::asio::ip::address::from_string("127.0.0.1"), 4848);
    _endpoint = serverEndpoint;
    _socket.open(_endpoint.protocol());

    // }
// }

// catch (std::exception &e) {
// 	std::cerr << "Error connecting to server: " <<e.what() << std::endl;
// }

    return (true);
}

void Network::ClientNetwork::initializeResponsehandler()
{
    _responseHandlers["pong\n"] = std::bind(&ClientNetwork::handlePong, this, std::placeholders::_1);
    _responseHandlers["200\n"] = std::bind(&ClientNetwork::handleConnection, this, std::placeholders::_1);
    _responseHandlers["201\n"] = std::bind(&ClientNetwork::handleLogin, this, std::placeholders::_1);
    _responseHandlers["202\n"] = std::bind(&ClientNetwork::handleLogout, this, std::placeholders::_1);
}

void Network::ClientNetwork::handlePong(const std::string &message)
{
    if (message == "ping") {
        mySend("pong");
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
