/*
** EPITECH PROJECT, 2023
** ClientNetwork.cpp
** File description:
** ClientNetwork
*/

#include "client/network/ClientNetwork.hpp"
#include "server/network/sendCode.hpp"

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
    if (!error && recvd_bytes > 0) {
        if (_data.size() >= HEADER_SIZE) {
            std::cout << "Je passe par la" << std::endl;
            header packet = getHeader(_data);
            // BodyNumber body = getBody(_data);
            // BodyNumber footer = getBody(_data);
            handleMessageData(packet, _data);
        }
        _data.clear();
        asyncReceive(_socket);
    } else {
        asyncReceive(_socket);
    }
}

void Network::ClientNetwork::handleSend(boost::system::error_code error, std::size_t recvd_bytes)
{
    asyncReceive(_socket);
}

void Network::ClientNetwork::sendHello()
{
    std::string res;

    res.append(Network::Send::makeBodyNum(81732));
    send(_tcpSocket, res);
}

void Network::ClientNetwork::sendMovement(Movement movement)
{
    int message;

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

    std::string res;
    res.append(Network::Send::makeBodyNum(message));

    asyncSend(_socket, res);
}

void Network::ClientNetwork::sendAction(Action action)
{
    int message;

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
    std::string res;
    res.append(Network::Send::makeBodyNum(message));
    asyncSend(_socket, res);
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
        }

        catch (std::exception &e) {
            std::cerr << "Error connecting to server: " << e.what() << std::endl;
            return (false);
        }
        return (true);
    }
}

void Network::ClientNetwork::initializeResponsehandler()
{
    _responseHandlers[200] = [this](const header &h, const std::string &s) {
        handleConnection(h, s);
        };
    _responseHandlers[201] = [this](const header &h, const std::string &s) {
        handleLogin(h, s);
        };
    _responseHandlers[202] = [this](const header &h, const std::string &s) {
        handleLogout(h, s);
        };
}

void Network::ClientNetwork::handleConnection(const header &messageHeader, const std::string &str)
{
    std::cout << "code: " << messageHeader.codeRfc << " entity: " << messageHeader.entity << std::endl;

    if (str.size() >= sizeof(header)) {
        int numClients = *reinterpret_cast<const int *>(str.c_str());
        std::cout << "Im the player " << messageHeader.entity << " and there are " << numClients << " players including you." << std::endl;
    } else {
        std::cout << "Unexpected message received" << std::endl;
    }
}

void Network::ClientNetwork::handleLogin(const header &messageHeader, const std::string &str)
{
    std::string strCopy = str;
    static bool firstTime = false;

    if (strCopy.size() >= sizeof(int)) {
        int udpPort = *reinterpret_cast<const int *>(strCopy.c_str());
        std::cout << "Im the player " << messageHeader.entity << " and this is the UDP port: " << udpPort << std::endl;

        strCopy.erase(0, sizeof(int));

        if (!strCopy.empty() && strCopy.size() >= sizeof(int)) {
            int additionalCode = *reinterpret_cast<const int *>(strCopy.c_str());
            std::cout << "Additional code: " << additionalCode << std::endl;
            if (additionalCode == 201 && !firstTime) {
                if (connect(_host, udpPort, false)) {
                    firstTime = true;
                    isConnectedUDP = true;
                    std::cout << "jme suis co en udp\n";
                } else {
                    std::cout << "jme suis pas co en udp\n";
                }
            }
        } else {
            std::cout << "Only header found" << std::endl;
        }
    } else {
        std::cout << "Unexpected message received" << std::endl;
    }
}

void Network::ClientNetwork::handleLogout(const header &messageHeader, const std::string &str)
{
    if (messageHeader.codeRfc == 202) {
        // std::cout << "Logged out as entity: " << entity << std::endl;
    } else {
        std::cout << "Unexpected message received" << std::endl;
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

void Network::ClientNetwork::enqueueReceivedMessage(const std::string &message)
{
    _receivedMessages.push(message);
}

void Network::ClientNetwork::handleNetwork()
{
    _ioService.reset();
    _ioService.poll();
}

void Network::ClientNetwork::stopIOService()
{
    _ioService.stop();
}

boost::asio::ip::udp::socket &Network::ClientNetwork::getUDPSocket()
{
    return _socket;
}

boost::asio::ip::tcp::socket &Network::ClientNetwork::getTCPSocket()
{
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

void Network::ClientNetwork::handleTCPData(const boost::system::error_code &error, std::size_t recvd_bytes, boost::asio::ip::tcp::socket &tcpsocket)
{
    if (!error && recvd_bytes > 0) {
        if (_data.size() >= (HEADER_SIZE)) {
            header packet = getHeader(_data);
            // BodyNumber body = getBody(_data);
            // BodyNumber footer = getBody(_data);
            handleMessageData(packet, _data);
        }
        startAsyncReceiveTCP(tcpsocket);
    } else {
        std::cerr << "Error receiving data: " << error.message() << std::endl;
    }
}

Network::BodyNumber Network::ClientNetwork::getBody(std::string &str)
{
    BodyNumber res;

    std::memcpy(&res, str.data(), sizeof(BodyNumber));
    // std::cout << "BodyNumber -> number: " << res.number << " garbage: " << res.garbage << std::endl;
    str.erase(0, sizeof(BodyNumber));
    return res;
}

void Network::ClientNetwork::startAsyncReceiveTCP(boost::asio::ip::tcp::socket &tcpsocket)
{
    _data.resize(MAX_SIZE_BUFF);
    tcpsocket.async_read_some(boost::asio::buffer(_data.data(), _data.size()), [this, &tcpsocket](boost::system::error_code error, std::size_t bytes_transferred) {
        handleTCPData(error, bytes_transferred, tcpsocket);
        });
}

Network::header Network::ClientNetwork::getHeader(std::string &str)
{
    header res;

    std::memcpy(&res, str.data(), HEADER_SIZE);
    std::cout << "Header -> code: " << res.codeRfc << " nb: " << res.entity << std::endl;
    str.erase(0, HEADER_SIZE);
    return res;
}

void Network::ClientNetwork::send201()
{
    std::string res;

    res.append(Network::Send::makeBodyNum(201));
    send(_tcpSocket, res);
}

void Network::ClientNetwork::handleMessageData(const header &messageHeader, std::string &str)
{
    auto responsehandlerIt = _responseHandlers.find(messageHeader.codeRfc);

    if (responsehandlerIt != _responseHandlers.end()) {
        responsehandlerIt->second(messageHeader, str);
    } else {
        std::cout << "Unexecepted message received" << std::endl;
    }
}
