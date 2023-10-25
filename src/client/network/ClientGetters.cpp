/*
** EPITECH PROJECT, 2023
** ClientGetters.cpp
** File description:
** ClientGetters
*/

#include "client/network/ClientNetwork.hpp"
#include "server/network/sendCode.hpp"
#include "ECS/Creator.hpp"
#include "GameEngine/GameEngine.hpp"

Network::ClientNetwork &Network::ClientNetwork::getInstance()
{
    if (_instance == nullptr) {
        throw std::runtime_error("ClientNetwork not initialized");
    }
    return *_instance;
}

Network::ClientNetwork &Network::ClientNetwork::getInstance(GameEngine::GameEngine &engine)
{
    if (_instance == nullptr) {
        _instance.reset(new ClientNetwork(engine));
    }
    return *_instance;
}

boost::asio::ip::udp::socket &Network::ClientNetwork::getUDPSocket()
{
    return _socket;
}

boost::asio::ip::tcp::socket &Network::ClientNetwork::getTCPSocket()
{
    return _tcpSocket;
}

Network::bodyMob Network::ClientNetwork::getMob(std::string &str)
{
    bodyMob res;

    std::memcpy(&res, str.data(), sizeof(bodyMob));
    str.erase(0, sizeof(bodyMob));
    return res;
}

Network::BodyNumber Network::ClientNetwork::getBody(std::string &str)
{
    BodyNumber res;

    std::memcpy(&res, str.data(), sizeof(BodyNumber));
    str.erase(0, sizeof(BodyNumber));
    return res;
}

Network::bodyAlly Network::ClientNetwork::getAlly(std::string &str)
{
    bodyAlly res;

    std::memcpy(&res, str.data(), sizeof(bodyAlly));
    str.erase(0, sizeof(bodyAlly));
    return res;
}

Network::bodyMissile Network::ClientNetwork::getMissile(std::string &str)
{
    bodyMissile res;

    std::memcpy(&res, str.data(), sizeof(bodyMissile));
    str.erase(0, sizeof(bodyMissile));
    return res;
}

boost::asio::ip::udp::endpoint Network::ClientNetwork::getLocalUDPEndpoint()
{
    return _socket.local_endpoint();
}

boost::asio::ip::tcp::endpoint Network::ClientNetwork::getLocalTCPEndpoint()
{
    return _tcpSocket.local_endpoint();
}

Network::header Network::ClientNetwork::getHeader(std::string &str)
{
    header res;

    std::memcpy(&res, str.data(), HEADER_SIZE);
    if (res.codeRfc != 0) {
        std::cout << "Header -> code: " << res.codeRfc << " nb: " << res.entity << std::endl;
    }
    str.erase(0, HEADER_SIZE);
    return res;
}
