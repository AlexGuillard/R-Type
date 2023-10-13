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
    : _ioService(std::ref(io_service)), _acceptor(_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), portTCP)), _asyncSocket(_ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), portUdp)),
    _timer(io_service), portUdp(portUdp)
{
    boost::asio::ip::tcp::resolver resolver(_ioService);
    boost::asio::ip::tcp::resolver::query query(boost::asio::ip::host_name(), "");
    boost::asio::ip::tcp::resolver::iterator endpoints = resolver.resolve(query);

    for (boost::asio::ip::tcp::resolver::iterator it = endpoints; it != boost::asio::ip::tcp::resolver::iterator(); ++it) {
        std::cout << "Server running on: " << it->endpoint().address().to_string() << ":" << std::to_string(_acceptor.local_endpoint().port()) << std::endl;
    }
    std::thread tcp(&Network::ServerNetwork::tcpConnection, this);
    std::thread udp(&Network::ServerNetwork::udpConnection, this);
    tcp.join();
    udp.join();
    _ioService.run();
}

Network::ServerNetwork::~ServerNetwork()
{}

void Network::ServerNetwork::tcpConnection()
{
    _acceptor.async_accept(std::bind(&Network::ServerNetwork::acceptHandler, this, std::placeholders::_1, std::placeholders::_2));
}

void Network::ServerNetwork::waitRequest(std::shared_ptr<boost::asio::ip::tcp::socket> &socket)
{
    int res = 0;

    _data.resize(MAX_SIZE_BUFF);
    socket->async_read_some(boost::asio::buffer(_data.data(), _data.size()), [this, &socket](boost::system::error_code error, std::size_t bytes_transferred) {
        int number = 0;

        if (!error) {
            if (findClient(getActualClient(*socket)) != "") {
                number = Network::Send::stringToInt(_data);
                std::cout << "[" << bytes_transferred << "] " << number << "from" << getActualClient(*socket) << std::endl;
                if (number == 201) {
                    Network::ServerNetwork::send201();
                }
            } else {
                connection(socket);
            }
            _data.clear();
            waitRequest(socket);
        } else {
            waitRequest(socket);
        }
        });
}

void Network::ServerNetwork::acceptHandler(const boost::system::error_code &error, boost::asio::ip::tcp::socket socket)
{
    static int nb = 0;

    if (!error && nb < 4) {
        std::cout << "acceptation success" << std::endl;
        _socket.push_back(std::make_shared<boost::asio::ip::tcp::socket>(std::move(socket)));
        std::cout << _socket.back()->remote_endpoint().address().to_string() << std::endl;
        waitRequest(_socket.back());
        nb++;
        _acceptor.async_accept(std::bind(&Network::ServerNetwork::acceptHandler, this, std::placeholders::_1, std::placeholders::_2));
    }
}

void Network::ServerNetwork::udpConnection()
{
    updateTicks();
    asyncReceive(_asyncSocket);
}

std::unordered_map<std::string, std::pair<int, std::vector<int>>> Network::ServerNetwork::getClientInputs()
{
    std::unordered_map<std::string, std::pair<int, std::vector<int>>> clientInputs;

    for (int i = 0; i < _clients.size(); i++) {
        std::string client = _clients[i];
        clientInputs[client] = std::make_pair(i, std::vector<int>());
    }
    return clientInputs;
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
        // host:ip -> {id, [RFC, ...]}
        std::unordered_map<std::string, std::pair<int, std::vector<int>>> clientInputs = getClientInputs();
        for (auto &&[client, data] : clientInputs) {
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
        updateTicks();
        });
}

void Network::ServerNetwork::handleReceive(boost::system::error_code error, std::size_t recvd_bytes)
{
    std::string actualClient;
    const size_t maxNbClients = 5;

    if (!error && recvd_bytes > 0) {
        if (findClient(getActualClient()) != "") {
            std::cout << "[" << recvd_bytes << "] " << Network::Send::stringToInt(_data) << "from" << getActualClient() << std::endl;
            asyncSend(_asyncSocket, "receive data\n");
        } else {
            asyncSend(_asyncSocket, "need tcp connection first\n");
        }
        _data.clear();
    } else {
        asyncReceive(_asyncSocket);
    }
}

void Network::ServerNetwork::addClient()
{
    std::string actualClient;

    if (_clients.size() < 4) {
        actualClient = _endpoint.address().to_string() + ":" + std::to_string(_endpoint.port());
        _clients.push_back(actualClient);
    }
}

std::string Network::ServerNetwork::getActualClient() const
{
    return _endpoint.address().to_string() + ":" + std::to_string(_endpoint.port());
}

std::string Network::ServerNetwork::getActualClient(boost::asio::ip::tcp::socket &socket) const
{
    return socket.remote_endpoint().address().to_string() + ":" + std::to_string(socket.remote_endpoint().port());
}

std::string Network::ServerNetwork::findClient(std::string findId) const
{
    auto res = std::find(_clients.begin(), _clients.end(), findId);

    if (res != _clients.end()) {
        return findId;
    }
    return "";
}

void Network::ServerNetwork::handleSend(boost::system::error_code error, std::size_t recvd_bytes)
{
    asyncReceive(_asyncSocket);
}

void Network::ServerNetwork::connection(std::shared_ptr<boost::asio::ip::tcp::socket> &socket)
{
    int number = Network::Send::stringToInt(_data);
    std::string actualClient;

    std::cout << number << std::endl;
    if (number == CONNECTION_NB && _clients.size() < 4) {
        actualClient = getActualClient(*socket);
        _clients.push_back(actualClient);
        _clientsTcp.push_back(socket);
        send(*socket, codeLogin(200));
        send202(_clientsTcp.size());
    } else {
        send(*socket, code401());
    }
}

bool Network::ServerNetwork::isGameRunning() const
{
    return this->isGame;
}

void Network::ServerNetwork::run(GameEngine::GameEngine &engine)
{
    _ioService.run();
    engine.run();
}

std::string Network::ServerNetwork::codeLogin(int code)
{
    std::string res;

    res = Network::Send::makeHeader(code, _clients.size() - 1);
    res.append(Network::Send::makeBinaryInt(_clients.size()));
    res.append(Network::Send::makeBinaryInt(code));
    return res;
}

std::string Network::ServerNetwork::code401()
{
    std::string res;

    res = Network::Send::makeHeader(401, -1);
    res.append(Network::Send::makeBinaryInt(401));
    return res;
}

void Network::ServerNetwork::send202(int indexClient)
{
    for (int i = 0; i < _clientsTcp.size(); i++) {
        if (indexClient != i)
            send(*_clientsTcp[i], codeLogin(202));
    }
}

void Network::ServerNetwork::send201()
{
    std::string res;

    res = Network::Send::makeHeader(201, -1);
    res.append(Network::Send::makeBinaryInt(portUdp));
    res.append(Network::Send::makeBinaryInt(201));
    for (int i = 0; i < _clientsTcp.size(); i++) {
        send(*_clientsTcp[i], res);
    }
}
