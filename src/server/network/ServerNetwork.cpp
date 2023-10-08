/*
** EPITECH PROJECT, 2023
** ServerNetwork.cpp
** File description:
** ServerNetwork
*/

#include "server/network/ServerNetwork.hpp"

Network::ServerNetwork::ServerNetwork(boost::asio::io_service& io_service, int port)
    : _ioService(std::ref(io_service)), _acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)), _asyncSocket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)), _timer(io_service)
{
    boost::asio::ip::udp::resolver resolver(_ioService);
    boost::asio::ip::udp::resolver::query query(boost::asio::ip::host_name(), "");
    boost::asio::ip::udp::resolver::iterator endpoints = resolver.resolve(query);

    for (boost::asio::ip::udp::resolver::iterator it = endpoints; it != boost::asio::ip::udp::resolver::iterator(); ++it) {
        std::cout << "Server running on: " << it->endpoint().address().to_string() << ":" << std::to_string(_acceptor.local_endpoint().port()) << std::endl;
    }
    while (1) {
        if (isGame == false) {
            tcpConnection();
        } else {
            udpConnection();
        }
        _ioService.run();
    }
}

Network::ServerNetwork::~ServerNetwork()
{}

void HandleRead(const boost::system::error_code& error, std::size_t bytes_transferred, std::shared_ptr<boost::asio::ip::tcp::socket> socket, std::vector<char>& buffer) {
    if (!error) {
        // Process the received data in the 'buffer' vector

        // Print the received data
        std::cout << "Received " << bytes_transferred << " bytes: " << std::string(buffer.begin(), buffer.begin() + bytes_transferred) << std::endl;

        // Start another asynchronous read operation
        socket->async_read_some(boost::asio::buffer(buffer), [socket, &buffer](const boost::system::error_code& read_error, std::size_t read_bytes) {
            HandleRead(read_error, read_bytes, socket, buffer);
        });
    } else {
        // std::cerr << "Error reading from client: " << error.message() << std::endl;
        socket->async_read_some(boost::asio::buffer(buffer), [socket, &buffer](const boost::system::error_code& read_error, std::size_t read_bytes) {
            HandleRead(read_error, read_bytes, socket, buffer);
        });
        // Handle the error, possibly by closing the socket
    }
}

void Network::ServerNetwork::tcpConnection()
{
    // _socket.push_back(std::make_shared<boost::asio::ip::tcp::socket>(_ioService));
    _acceptor.async_accept(std::bind(&Network::ServerNetwork::acceptHandler, this, std::placeholders::_1, std::placeholders::_2));
}

void Network::ServerNetwork::waitRequest(boost::asio::ip::tcp::socket &socket)
{
    // auto self(shared_from_this());
    _data.resize(MAX_SIZE_BUFF);
    socket.async_read_some(boost::asio::buffer(_data.data(), _data.size()), [this, &socket](boost::system::error_code error, std::size_t bytes_transferred) {
        // HandleRead(read_error, read_bytes, socket[nb], _data);
        if (!error) {
            // Process the received data in the 'buffer' vector

            // Print the received data
            std::cout << "Received " << bytes_transferred << " bytes: " << _data.data() << std::endl;

            _data.clear();
            // Start another asynchronous read operation
            waitRequest(socket);
        } else {
            // std::cerr << "Error reading from client: " << error.message() << std::endl;
            waitRequest(socket);
            // Handle the error, possibly by closing the socket
        }
    });
}

void Network::ServerNetwork::acceptHandler(const boost::system::error_code& error, boost::asio::ip::tcp::socket socket)
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
    asyncReceive(_asyncSocket);
}

void Network::ServerNetwork::connection()
{
    std::string res = _data.data();

    if (res == "Hello R-Type server\n" && _clients.size() < 5) {
        addClient();
        asyncSend(_asyncSocket, "200\n");
    } else {
        asyncSend(_asyncSocket, "401: Forbidden\n");
    }
}
