/*
** EPITECH PROJECT, 2023
** ServerNetwork.cpp
** File description:
** ServerNetwork
*/

#include <iostream>
#include <unordered_map>
#include <string>
#include <utility>
#include "server/network/ServerNetwork.hpp"
#include "server/network/sendCode.hpp"
#include "GameEngine/Events.hpp"
#include "enums.hpp"

Network::ServerNetwork::ServerNetwork(boost::asio::io_service &io_service, int portTCP, int portUdp)
    : _ioService(std::ref(io_service)), _acceptor(_ioService), _asyncSocket(_ioService),
    _timer(io_service), _portUdp(portUdp)
{
    boost::asio::ip::tcp::resolver resolver(_ioService);
    boost::asio::ip::tcp::resolver::query query(boost::asio::ip::host_name(), "");
    boost::asio::ip::tcp::resolver::iterator endpoints = resolver.resolve(query);

    portTCP = setTcpSocket(portTCP);
    if (portTCP == -1)
        throw std::runtime_error("Can not set server tcp");
    _portUdp = setUdpSocket(portUdp);
    if (_portUdp == -1)
        throw std::runtime_error("Can not set server udp");
    std::cout << "tcp on " << portTCP << std::endl;
    std::cout << "udp on " << _portUdp << std::endl;
    for (boost::asio::ip::tcp::resolver::iterator it = endpoints; it != boost::asio::ip::tcp::resolver::iterator(); ++it) {
        std::cout << "Server running on: " << it->endpoint().address().to_string() << ":" << std::to_string(_acceptor.local_endpoint().port()) << std::endl;
    }
    _tcp.reset(new std::thread(&Network::ServerNetwork::tcpConnection, this));
    _udp.reset(new std::thread(&Network::ServerNetwork::udpConnection, this));
}

Network::ServerNetwork::~ServerNetwork()
{
    _acceptor.close();
    _asyncSocket.close();
    _tcp->join();
    _udp->join();
    _ioService.stop();
}

int Network::ServerNetwork::setUdpSocket(int port)
{
    boost::system::error_code error;
    static int index = 0;

    if (!_asyncSocket.is_open()) {
        _asyncSocket.open(boost::asio::ip::udp::v4(), error);
    }
    if (error) {
        index++;
        if (index == 65535) {
            return -1;
        }
        return setUdpSocket(port + 1);
    }
    _endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address_v4::any(), port);
    _asyncSocket.bind(_endpoint, error);
    if (error) {
        index++;
        if (index == 65535) {
            return -1;
        }
        return setUdpSocket(port + 1);
    }
    return port;
}

int Network::ServerNetwork::setTcpSocket(int port)
{
    boost::system::error_code error;
    boost::asio::ip::tcp::endpoint end;
    static int index = 0;

    if (!_acceptor.is_open()) {
        _acceptor.open(boost::asio::ip::tcp::v4(), error);
    }
    if (error) {
        index++;
        if (index == 65535) {
            return -1;
        }
        return setTcpSocket(port + 1);
    }
    end = boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::any(), port);
    _acceptor.bind(end, error);
    if (error) {
        index++;
        if (index == 65535) {
            return -1;
        }
        return setTcpSocket(port + 1);
    }
    _acceptor.listen();
    return port;
}

void Network::ServerNetwork::tcpConnection()
{
    _acceptor.async_accept(std::bind(&Network::ServerNetwork::acceptHandler, this, std::placeholders::_1, std::placeholders::_2));
}

void Network::ServerNetwork::acceptHandler(const boost::system::error_code &error, boost::asio::ip::tcp::socket socket)
{
    if (!error) {
        std::cout << "acceptation success" << std::endl;
        std::make_shared<Network::ServerTcp>(std::move(socket), _list, _portUdp, _clients, _isGame)->start();
    }
    _acceptor.async_accept(std::bind(&Network::ServerNetwork::acceptHandler, this, std::placeholders::_1, std::placeholders::_2));
}

void Network::ServerNetwork::udpConnection()
{
    updateTicks();
    asyncReceive(_asyncSocket);
}

void Network::ServerNetwork::updateTicks()
{
    _timer.expires_from_now(boost::posix_time::millisec(TICKS_UPDATE));
    _timer.async_wait([this](const boost::system::error_code &error) {
        if (error) {
            std::cerr << "_timer error: " << error.message() << std::endl;
            updateTicks();
            return;
        }
        if (_isGame == true) {
            _tickCount++;
            // host:ip -> {id, [RFC, ...]}
            for (auto &&[client, data] : _clients) {
                auto &&[id, inputs] = data;
                for (auto &&input : inputs) {
                    switch (input) {
                    case static_cast<int>(Enums::RFCCode::PLAYER_UP):
                        GameEngine::Events::push(GameEngine::Events::Type::PLAYER_UP, id);
                        break;
                    case static_cast<int>(Enums::RFCCode::PLAYER_DOWN):
                        GameEngine::Events::push(GameEngine::Events::Type::PLAYER_DOWN, id);
                        break;
                    case static_cast<int>(Enums::RFCCode::PLAYER_LEFT):
                        GameEngine::Events::push(GameEngine::Events::Type::PLAYER_LEFT, id);
                        break;
                    case static_cast<int>(Enums::RFCCode::PLAYER_RIGHT):
                        GameEngine::Events::push(GameEngine::Events::Type::PLAYER_RIGHT, id);
                        break;
                    case static_cast<int>(Enums::RFCCode::PLAYER_SHOOT):
                        GameEngine::Events::push(GameEngine::Events::Type::PLAYER_SHOOT, id);
                        break;
                    case static_cast<int>(Enums::RFCCode::PLAYER_DROP):
                        GameEngine::Events::push(GameEngine::Events::Type::PLAYER_DROP, id);
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        updateTicks();
        });
}

void Network::ServerNetwork::handleReceive(boost::system::error_code error, std::size_t recvd_bytes)
{
    std::string actualClient;
    const size_t maxNbClients = 5;

    if (!error && recvd_bytes >= sizeof(BodyNumber)) {
        if (findClient(getActualClient()) != "") {
        BodyNumber num = { 0 };
        num = Network::Send::stringToBodyNum(_data);
        if (num.number != -1) {
            handleClientData(num.number);
            std::cout << "[" << recvd_bytes << "] " << num.number << "from" << getActualClient() << std::endl;
        }
        _data.clear();
        asyncSend(_asyncSocket, "receive data\n");
    } else {
        asyncSend(_asyncSocket, "need tcp connection first\n");
    }
        asyncReceive(_asyncSocket);
    } else {
        asyncReceive(_asyncSocket);
    }
}

std::string Network::ServerNetwork::getActualClient() const
{
    return _endpoint.address().to_string() + ":" + std::to_string(_endpoint.port());
}

std::string Network::ServerNetwork::findClient(std::string findId) const
{
    if (_clients.contains(findId)) {
        return findId;
    }
    return "";
}

void Network::ServerNetwork::handleSend(boost::system::error_code error, std::size_t recvd_bytes)
{
    asyncReceive(_asyncSocket);
}

bool Network::ServerNetwork::isGameRunning() const
{
    return this->_isGame;
}

void Network::ServerNetwork::run(GameEngine::GameEngine &engine)
{
    _ioService.poll();
    _ioService.reset();
    engine.run();
}

void Network::ServerNetwork::handleClientData(int num)
{
    if (num >= 211 && num <= 216) {
        _clients[getActualClient()].second.push_back(num);
    }
}
