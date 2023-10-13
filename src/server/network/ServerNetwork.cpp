/*
** EPITECH PROJECT, 2023
** ServerNetwork.cpp
** File description:
** ServerNetwork
*/

#include "server/network/ServerNetwork.hpp"

Network::ServerNetwork::ServerNetwork(boost::asio::io_service &io_service, int portTCP, int portUdp)
    : _ioService(std::ref(io_service)), _acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), portTCP)), _asyncSocket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), portUdp)), _timer(io_service), portUdp(portUdp)
{
    boost::asio::ip::tcp::resolver resolver(_ioService);
    boost::asio::ip::tcp::resolver::query query(boost::asio::ip::host_name(), "");
    boost::asio::ip::tcp::resolver::iterator endpoints = resolver.resolve(query);

    for (boost::asio::ip::tcp::resolver::iterator it = endpoints; it != boost::asio::ip::tcp::resolver::iterator(); ++it) {
        std::cout << "Server running on: " << it->endpoint().address().to_string() << ":" << std::to_string(_acceptor.local_endpoint().port()) << std::endl;
    }
}

Network::ServerNetwork::~ServerNetwork()
{}

void Network::ServerNetwork::tcpConnection()
{
    _acceptor.async_accept(std::bind(&Network::ServerNetwork::acceptHandler, this, std::placeholders::_1, std::placeholders::_2));
}

void Network::ServerNetwork::waitRequest(boost::asio::ip::tcp::socket &socket)
{
    _data.resize(MAX_SIZE_BUFF);
    socket.async_read_some(boost::asio::buffer(_data.data(), _data.size()), [this, &socket](boost::system::error_code error, std::size_t bytes_transferred) {
        if (!error) {
            if (findClient(getActualClient(socket)) != "") {
                std::cout << "[" << bytes_transferred << "] " << _data.data() << "from" << getActualClient(socket) << std::endl;
            } else {
                connection(socket);
            }
            _data.clear();
            // Start another asynchronous read operation
            waitRequest(socket);
        } else {
            waitRequest(socket);
            // Handle the error, possibly by closing the socket
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
        waitRequest(*_socket.back());
        nb++;
        _acceptor.async_accept(std::bind(&Network::ServerNetwork::acceptHandler, this, std::placeholders::_1, std::placeholders::_2));
    }
}

void Network::ServerNetwork::udpConnection()
{
    updateTicks();
    asyncReceive(_asyncSocket);
}

void Network::ServerNetwork::updateTicks()
{
    int timerTicks = 200;

    _timer.expires_from_now(boost::posix_time::millisec(timerTicks));
    _timer.async_wait([this](const boost::system::error_code &error) {
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

    if (!error && recvd_bytes > 0) {
        if (findClient(getActualClient()) != "") {
            std::cout << "[" << recvd_bytes << "] " << _data.data() << "from" << getActualClient() << std::endl;
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

void Network::ServerNetwork::connection(boost::asio::ip::tcp::socket &socket)
{
    std::string res = _data.data();
    std::string actualClient;

    if (res == "Hello R-Type server\n" && _clients.size() < 4) {
        actualClient = getActualClient(socket);
        _clients.push_back(actualClient);
        res = std::to_string(portUdp);
        send(socket, "200\n");
        send(socket, res);
    } else {
        send(socket, "401: Forbidden\n");
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

std::string Network::ServerNetwork::makeHeader(int code, int entityNb)
{
    header res;
    std::string str;

    str.resize(sizeof(header));
    res.codeRfc = code;
    res.entity = entityNb;
    std::memcpy(str.data(), &res, sizeof(header));
    return str;
}
