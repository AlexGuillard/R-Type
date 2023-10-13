/*
** EPITECH PROJECT, 2023
** ClientNetwork.cpp
** File description:
** ClientNetwork
*/

#include "client/network/ClientNetwork.hpp"

Network::ClientNetwork::ClientNetwork(boost::asio::io_service &io_service, const std::string &host, int port) : _port(port), _host(host), _socket(io_service), _tcpSocket(io_service)
{
    boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string(host), port);
    _endpoint = endpoint;
    _socket.open(endpoint.protocol());

    initializeResponsehandler();
    sendHello();
}

Network::ClientNetwork::ClientNetwork() : _port(0), _socket(_ioService), _tcpSocket(_ioService)
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
    asyncReceive(_socket);
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
    send(_tcpSocket, "Hello R-Type server\n");
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

bool Network::ClientNetwork::connect(const std::string &host, int port, bool isTCP)
{
    if (isTCP) {
        connectTCP(host, port);
        sendHello();
        return (true);
    } else {
        try {
            boost::asio::ip::udp::endpoint serverEndpoint(boost::asio::ip::address::from_string(host), port);
            _endpoint = serverEndpoint;
            _socket.open(_endpoint.protocol());
            std::cout << "Connected to server by udp" << std::endl;
        }

        catch (std::exception &e) {
        	std::cerr << "Error connecting to server: " <<e.what() << std::endl;
            return (false);
        }
        return (true);
    }
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

boost::asio::ip::udp::socket& Network::ClientNetwork::getUDPSocket() {
    return _socket;
}

boost::asio::ip::tcp::socket& Network::ClientNetwork::getTCPSocket() {
    return _tcpSocket;
}

bool Network::ClientNetwork::connectTCP(const std::string &host, int port)
{
    try {
        boost::asio::ip::tcp::resolver resolver(_ioService);
        boost::asio::ip::tcp::resolver::query query(host, std::to_string(port));
        boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        boost::asio::connect(_tcpSocket, endpoint_iterator);

        std::cout << "Connected to server by tcp" << std::endl;

        return (true);
    }

    catch (std::exception &e) {
        std::cerr << "Error connecting to TCP server: " << e.what() << std::endl;
        return (false);
    }
}

void Network::ClientNetwork::handleTCPData(const boost::system::error_code& error, std::size_t recvd_bytes, boost::asio::ip::tcp::socket &tcpsocket)
{
    if (!error && recvd_bytes > 0) {
        std::cout << "[" << recvd_bytes << "] " << _data.data() << std::endl;
        startAsyncReceiveTCP(tcpsocket);
    } else {
        std::cerr << "Error receiving data: " << error.message() << std::endl;
    }
}

void Network::ClientNetwork::startAsyncReceiveTCP(boost::asio::ip::tcp::socket &tcpsocket)
{
    _data.resize(MAX_SIZE_BUFF);
    tcpsocket.async_read_some(boost::asio::buffer(_data.data(), _data.size()), [this, &tcpsocket](boost::system::error_code error, std::size_t bytes_transferred) {
        handleTCPData(error, bytes_transferred, tcpsocket);
    });
}
