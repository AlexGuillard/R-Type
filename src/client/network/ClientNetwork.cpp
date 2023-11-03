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
    _errorServer = false;
    initializeResponsehandler();
    initializeTCPResponsehandler();
}

Network::ClientNetwork::~ClientNetwork()
{}

//-----------------------------SEND--------------------------------------------//

void Network::ClientNetwork::sendHello(Enums::MultiState state)
{
    std::string res = "";

    res = Network::Send::makeHeader(CONNECTION_NB, 5);
    if (state == Enums::MultiState::SOLO) {
        res.append(Network::Send::makeHeader(203, 5));
    } else {
        res.append(Network::Send::makeHeader(204, 5));
    }
    send(_tcpSocket, res);
}

void Network::ClientNetwork::sendMovement(Movement movement)
{
    int message = 0;

    switch (movement) {
    case Movement::UP:
        message = static_cast<int>(Enums::RFCCode::PLAYER_UP);
        break;
    case Movement::DOWN:
        message = static_cast<int>(Enums::RFCCode::PLAYER_DOWN);
        break;
    case Movement::LEFT:
        message = static_cast<int>(Enums::RFCCode::PLAYER_LEFT);
        break;
    case Movement::RIGHT:
        message = static_cast<int>(Enums::RFCCode::PLAYER_RIGHT);
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

void Network::ClientNetwork::send201(Enums::ModeSelect mode)
{
    std::string res = "";

    switch (mode) {
        case Enums::ModeSelect::REGULAR:
            res.append(Network::Send::makeHeader(241, _indexPlayer));
            break;
        case Enums::ModeSelect::INFINI:
            res.append(Network::Send::makeHeader(242, _indexPlayer));
            break;
        case Enums::ModeSelect::FRIENDLYFIRE:
            res.append(Network::Send::makeHeader(243, _indexPlayer));
            break;
        case Enums::ModeSelect::PVP:
            res.append(Network::Send::makeHeader(244, _indexPlayer));
            break;
        default:
            break;
    }
    send(_tcpSocket, res);
}

bool Network::ClientNetwork::connect(const std::string &host, int port, bool isTCP, Enums::MultiState state)
{
    if (isTCP) {
        if (!connectTCP(host, port)) {
            return false;
        }
        sendHello(state);
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
            asyncReceive(_socket);
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
    _ioService.poll();
}

void Network::ClientNetwork::handleReceive(boost::system::error_code error, std::size_t recvd_bytes)
{
    std::string received = std::string(_data.begin(), _data.begin() + recvd_bytes);
    _data.erase(0, recvd_bytes);
    asyncReceive(_socket);
    if (!error && recvd_bytes > HEADER_SIZE) {
        while (received.size() > HEADER_SIZE) {
            header packet = getHeader(received);
            handleMessageData(packet, received);
        }
        received.clear();
    } else {
        std::cerr << "Error receiving data: " << error.message() << std::endl;
        received.clear();
    }
}

void Network::ClientNetwork::handleSend(boost::system::error_code error, std::size_t recvd_bytes)
{
    if (error) {
        std::cerr << "Error sending data: " << error.message() << std::endl;
    }
}

void Network::ClientNetwork::stopIOService()
{
    _ioService.stop();
}

bool Network::ClientNetwork::connectTCP(const std::string &host, int port)
{
    try {
        boost::asio::ip::tcp::endpoint serverEndpoint(boost::asio::ip::address::from_string(host), port);
        _tcpSocket.connect(serverEndpoint);

        std::cout << "Connected to server by tcp" << std::endl;

        return (true);
    } catch (std::exception &e) {
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
