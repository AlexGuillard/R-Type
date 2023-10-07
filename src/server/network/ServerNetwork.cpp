/*
** EPITECH PROJECT, 2023
** ServerNetwork.cpp
** File description:
** ServerNetwork
*/

#include "server/network/ServerNetwork.hpp"

Network::ServerNetwork::ServerNetwork(boost::asio::io_service& io_service, int port)
    : _ioService(io_service), _acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)), _asyncSocket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)), _timer(io_service)
{
    _socket.push_back(boost::asio::ip::tcp::socket(_ioService));
    _acceptor.async_accept(_socket.back(), std::bind(&Network::ServerNetwork::acceptHandler, this, std::placeholders::_1));
    updateTicks();
    receive(_asyncSocket);
}

Network::ServerNetwork::~ServerNetwork()
{}

void Network::ServerNetwork::acceptHandler(const boost::system::error_code& error)
{
    if (!error) {
        std::cout << "acceptation success" << std::endl;
    }
    _socket.push_back(boost::asio::ip::tcp::socket(_ioService));
    _acceptor.async_accept(_socket.back(), std::bind(&Network::ServerNetwork::acceptHandler, this, std::placeholders::_1));
}

void Network::ServerNetwork::updateTicks()
{
    int timerTicks = 200;

    _timer.expires_from_now(boost::posix_time::millisec(timerTicks));
    _timer.async_wait([this](const boost::system::error_code& error) {
        if (!error) {
            // std::cout << "need to updates ticks\n";
        } else {
            std::cerr << "_timer error: " << error.message() << std::endl;
        }
        updateTicks();
    });
}

void Network::ServerNetwork::handleReceive(boost::system::error_code error, std::size_t recvd_bytes)
{
    std::string actualClient;
    const size_t maxNbClients = 5;

    if ( !error && recvd_bytes > 0 ) {
        if (findClient(getActualClient()) != "") {
            std::cout << "[" << recvd_bytes << "] " << _data.data() << "from" << getActualClient() << std::endl;
            send(_asyncSocket, "receive data\n");
        } else {
            send(_asyncSocket, "need tcp connection first\n");
        }
        _data.clear();
    } else {
        receive(_asyncSocket);
    }
}

void Network::ServerNetwork::addClient()
{
    std::string actualClient;

    if (_clients.size() < 5) {
        actualClient = _endpoint.address().to_string() + ":" + std::to_string(_endpoint.port());
        _clients.push_back(actualClient);
    }
}

std::string Network::ServerNetwork::getActualClient() const
{
    return _endpoint.address().to_string() + ":" + std::to_string(_endpoint.port());
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
    receive(_asyncSocket);
}

void Network::ServerNetwork::connection()
{
    std::string res = _data.data();

    if (res == "Hello R-Type server\n" && _clients.size() < 5) {
        addClient();
        send(_asyncSocket, "200\n");
    } else {
        send(_asyncSocket, "401: Forbidden\n");
    }
}
