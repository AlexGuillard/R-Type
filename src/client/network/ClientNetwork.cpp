/*
** EPITECH PROJECT, 2023
** ClientNetwork.cpp
** File description:
** ClientNetwork
*/

#include "client/network/ClientNetwork.hpp"
#include "server/network/sendCode.hpp"
#include "ECS/Creator.hpp"
#include "GameEngine/GameEngine.hpp"

//-----------------------------CONSTRUCTOR / DESTRUCTOR--------------------------------------------//

Network::ClientNetwork::ClientNetwork(GameEngine::GameEngine &engine)
    : _port(0), _socket(_ioService), _tcpSocket(_ioService), _engine(engine)
{
    initializeResponsehandler();
    initializeTCPResponsehandler();
}

Network::ClientNetwork::~ClientNetwork()
{}

//-----------------------------SEND--------------------------------------------//

void Network::ClientNetwork::sendHello()
{
    std::string res = "";

    res = Network::Send::makeHeader(CONNECTION_NB, 5);
    send(_tcpSocket, res);
}

void Network::ClientNetwork::sendMovement(Movement movement)
{
    int message = 0;

    switch (movement) {
    case Movement::UP:
        message = 211;
        break;
    case Movement::DOWN:
        message = 212;
        break;
    case Movement::LEFT:
        message = 213;
        break;
    case Movement::RIGHT:
        message = 214;
        break;
    default:
        break;
    }

    std::string res = "";
    res.append(Network::Send::makeHeader(message, _indexPlayer));

    asyncSend(_socket, res);
}

void Network::ClientNetwork::sendAction(Action action)
{
    int message = 0;

    switch (action) {
    case Action::SHOOT:
        message = 215;
        break;
    case Action::DROP:
        message = 216;
        break;
    default:
        break;
    }
    std::string res = "";
    res.append(Network::Send::makeHeader(message, _indexPlayer));
    asyncSend(_socket, res);
}

void Network::ClientNetwork::send201()
{
    std::string res = "";

    res = Network::Send::makeHeader(201, _indexPlayer);
    send(_tcpSocket, res);
}

bool Network::ClientNetwork::connect(const std::string &host, int port, bool isTCP)
{
    if (isTCP) {
        connectTCP(host, port);
        sendHello();
        _host = host;
        return (true);
    } else {
        try {
            boost::asio::ip::udp::endpoint serverEndpoint(boost::asio::ip::address::from_string(host), port);
            _endpoint = serverEndpoint;
            _socket.open(_endpoint.protocol());
            std::cout << "Connected to server by udp" << std::endl;

            std::string res = "";
            res = Network::Send::makeHeader(217, _indexPlayer);
            asyncSend(_socket, res);
        }

        catch (std::exception &e) {
            std::cerr << "Error connecting to server: " << e.what() << std::endl;
            return (false);
        }
        return (true);
    }
}

//-----------------------------HANDLE NETWORK--------------------------------------------//

void Network::ClientNetwork::handleTCPData(const boost::system::error_code &error, std::size_t recvd_bytes, boost::asio::ip::tcp::socket &tcpsocket)
{
    std::string received = std::string(_data.begin(), _data.begin() + recvd_bytes);
    _data.erase(0, recvd_bytes);
    if (!error && recvd_bytes > HEADER_SIZE) {
        while (received.size() > HEADER_SIZE) {
            header packet = getHeader(received);
            handleTCPMessageData(packet, received);
        }
    } else {
        std::cerr << "Error receiving data: " << error.message() << std::endl;
    }
    received.clear();
    startAsyncReceiveTCP(tcpsocket);
}

void Network::ClientNetwork::handleNetwork()
{
    _ioService.reset();
    _ioService.poll_one();
}

void Network::ClientNetwork::handleReceive(boost::system::error_code error, std::size_t recvd_bytes)
{
    _data = std::string(_data.begin(), _data.begin() + recvd_bytes);
    if (!error && recvd_bytes > HEADER_SIZE) {
        while (_data.size() > HEADER_SIZE) {
            header packet = getHeader(_data);
            handleMessageData(packet, _data);
        }
        _data.clear();
    } else {
        std::cerr << "Error receiving data: " << error.message() << std::endl;
        _data.clear();
    }
    asyncReceive(_socket);
}

void Network::ClientNetwork::handleSend(boost::system::error_code error, std::size_t recvd_bytes)
{
    asyncReceive(_socket);
}

void Network::ClientNetwork::stopIOService()
{
    _ioService.stop();
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

void Network::ClientNetwork::enqueueReceivedMessage(const std::string &message)
{
    _receivedMessages.push(message);
}

void Network::ClientNetwork::startAsyncReceiveTCP(boost::asio::ip::tcp::socket &tcpsocket)
{
    _data.resize(MAX_SIZE_BUFF);
    tcpsocket.async_read_some(boost::asio::buffer(_data.data(), _data.size()), [this, &tcpsocket](boost::system::error_code error, std::size_t bytes_transferred) {
        handleTCPData(error, bytes_transferred, tcpsocket);
        });
}

//-----------------------------ENGINE--------------------------------------------//

void Network::ClientNetwork::setEngine(GameEngine::GameEngine &engine)
{
    _engine = engine;
}

std::unique_ptr<Network::ClientNetwork> Network::ClientNetwork::_instance = std::unique_ptr<Network::ClientNetwork>();
