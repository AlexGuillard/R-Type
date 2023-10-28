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
#include "enums.hpp"

//-----------------------------CONSTRUCTOR / DESTRUCTOR--------------------------------------------//

Network::ClientNetwork::ClientNetwork(GameEngine::GameEngine &engine)
    : _port(0), _socket(_ioService), _tcpSocket(_ioService), _engine(engine)
{
    initializeResponsehandler();
}

Network::ClientNetwork::~ClientNetwork()
{}

//-----------------------------SEND--------------------------------------------//

void Network::ClientNetwork::sendHello()
{
    std::string res;

    res = Network::Send::makeHeader(CONNECTION_NB, 5);
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

    std::string res;
    res.append(Network::Send::makeBodyNum(message));

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
    std::string res;
    res.append(Network::Send::makeBodyNum(message));
    asyncSend(_socket, res);
}

void Network::ClientNetwork::send201()
{
    std::string res;

    res = Network::Send::makeHeader(201, _indexPlayer);
    send(_tcpSocket, res);
}

//-----------------------------HANDLE MESSAGES--------------------------------------------//

void Network::ClientNetwork::initializeResponsehandler()
{
    // connection
    _responseHandlers[200] = [this](const header &h, std::string &s) {
        handleConnection(h, s);
        };
    _responseHandlers[201] = [this](const header &h, std::string &s) {
        handleLogin(h, s);
        };
    _responseHandlers[202] = [this](const header &h, std::string &s) {
        handleLogout(h, s);
        };

    // players
    _responseHandlers[311] = [this](const header &h, std::string &s) {
        handlePlayerSpawn(h, s);
        };
    _responseHandlers[312] = [this](const header &h, std::string &s) {
        handleAllySpawn(h, s);
        };

    // mobs
    _responseHandlers[301] = [this](const header &h, std::string &s) {
        handlePataPataSpawn(h, s);
        };
    _responseHandlers[302] = [this](const header &h, std::string &s) {
        handleBinkSpawn(h, s);
        };
    _responseHandlers[303] = [this](const header &h, std::string &s) {
        handleScantSpawn(h, s);
        };
    _responseHandlers[304] = [this](const header &h, std::string &s) {
        handleBugSpawn(h, s);
        };
    _responseHandlers[305] = [this](const header &h, std::string &s) {
        handleCancerSpawn(h, s);
        };
    _responseHandlers[306] = [this](const header &h, std::string &s) {
        handleBlasterSpawn(h, s);
        };
}

//-----------------------------MOBS--------------------------------------------//

void Network::ClientNetwork::handleBlasterSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyMob mobData = getMob(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 306) {
            std::cout << "Entity: " << messageHeader.entity << " X: " << mobData.x << " Y: " << mobData.y << " Color: " << static_cast<int>(mobData.pos) << std::endl;
            ECS::Creator::createCancer(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, mobData.x, mobData.y);
        }
    } else {
        std::cout << "Unexpected message received player" << std::endl;
    }
}

void Network::ClientNetwork::handleCancerSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyMob mobData = getMob(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 305) {
            std::cout << "Entity: " << messageHeader.entity << " X: " << mobData.x << " Y: " << mobData.y << " Color: " << static_cast<int>(mobData.pos) << std::endl;
            ECS::Creator::createCancer(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, mobData.x, mobData.y);
        }
    } else {
        std::cout << "Unexpected message received player" << std::endl;
    }
}

void Network::ClientNetwork::handleBugSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyMob mobData = getMob(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 304) {
            std::cout << "Entity: " << messageHeader.entity << " X: " << mobData.x << " Y: " << mobData.y << " Color: " << static_cast<int>(mobData.pos) << std::endl;
            ECS::Creator::createBug(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, mobData.x, mobData.y);
        }
    } else {
        std::cout << "Unexpected message received player" << std::endl;
    }
}

void Network::ClientNetwork::handleScantSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyMob mobData = getMob(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 303) {
            std::cout << "Entity: " << messageHeader.entity << " X: " << mobData.x << " Y: " << mobData.y << " Color: " << static_cast<int>(mobData.pos) << std::endl;
            ECS::Creator::createScant(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, mobData.x, mobData.y);
        }
    } else {
        std::cout << "Unexpected message received player" << std::endl;
    }
}

void Network::ClientNetwork::handleBinkSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyMob mobData = getMob(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 302) {
            std::cout << "Entity: " << messageHeader.entity << " X: " << mobData.x << " Y: " << mobData.y << " Color: " << static_cast<int>(mobData.pos) << std::endl;
            ECS::Creator::createBink(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, mobData.x, mobData.y);
        }
    } else {
        std::cout << "Unexpected message received player" << std::endl;
    }
}

void Network::ClientNetwork::handlePataPataSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyMob mobData = getMob(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 301) {
            std::cout << "Entity: " << messageHeader.entity << " X: " << mobData.x << " Y: " << mobData.y << " Color: " << static_cast<int>(mobData.pos) << std::endl;
            ECS::Creator::createEnemyBasic(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, mobData.x, mobData.y);
        }
    } else {
        std::cout << "Unexpected message received player" << std::endl;
    }
}

//-----------------------------PLAYERS--------------------------------------------//

void Network::ClientNetwork::handlePlayerSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyAlly allyData = getAlly(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 311) {
            std::cout << "Entity: " << messageHeader.entity << " X: " << allyData.x << " Y: " << allyData.y << " Color: " << static_cast<int>(allyData.color) << std::endl;
            ECS::Creator::createPlayer(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, allyData.x, allyData.y, allyData.color);
        }
    } else {
        std::cout << "Unexpected message received player" << std::endl;
    }
}

void Network::ClientNetwork::handleAllySpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyAlly allyData = getAlly(str);
        BodyNumber footer = getBody(str);

        std::cout << "received " << footer.number << std::endl;
        if (footer.number == 312) {
            std::cout << "Ally : " << messageHeader.entity << " X: " << allyData.x << " Y: " << allyData.y << " Color: " << static_cast<int>(allyData.color) << std::endl;
            ECS::Creator::createAlly(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, allyData.x, allyData.y, allyData.color);
        }

    } else {
        std::cout << "Unexpected message received ally" << std::endl;
    }
}

//-----------------------------CONNECTION--------------------------------------------//

void Network::ClientNetwork::handleConnection(const header &messageHeader, std::string &str)
{
    if (messageHeader.codeRfc != 0)
        std::cout << "code: " << messageHeader.codeRfc << " entity: " << messageHeader.entity << std::endl;

    if (str.size() >= sizeof(BodyNumber) + sizeof(BodyNumber)) {
        BodyNumber numClients = getBody(str);
        BodyNumber footer = getBody(str);
        std::cout << "Im the player " << messageHeader.entity << " and there are " << numClients.number << " players including you." << std::endl;
        std::cout << "footer" << footer.number << std::endl;
        _indexPlayer = messageHeader.entity;
    } else {
        std::cout << "Unexpected message received connection" << std::endl;
    }
}

void Network::ClientNetwork::handleLogin(const header &messageHeader, std::string &str)
{
    static bool firstTime = false;

    if (str.size() >= sizeof(BodyNumber)) {
        BodyNumber udpPort = getBody(str);
        std::cout << "Im the player " << messageHeader.entity << " and this is the UDP port: " << udpPort.number << std::endl;

        if (!str.empty() && str.size() >= sizeof(BodyNumber)) {

            BodyNumber footer = getBody(str);
            std::cout << "Additional code: " << footer.number << std::endl;

            if (footer.number == 201 && !firstTime) {
                if (connect(_host, udpPort.number, false)) {
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
        std::cout << "Unexpected message received on login" << std::endl;
    }
}

void Network::ClientNetwork::handleLogout(const header &messageHeader, std::string &str)
{
    if (messageHeader.codeRfc == 202) {
        // std::cout << "Logged out as entity: " << entity << std::endl;
    } else {
        std::cout << "Unexpected message received logout" << std::endl;
    }
}

void Network::ClientNetwork::handleMessageData(const header &messageHeader, std::string &str)
{
    auto responsehandlerIt = _responseHandlers.find(messageHeader.codeRfc);

    if (responsehandlerIt != _responseHandlers.end()) {
        responsehandlerIt->second(messageHeader, str);
    } else {
        // std::cout << "Unexecepted message received message data" << std::endl;
    }
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

            std::string res;
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

//-------------------------------GETTERS------------------------------------------//

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

//-----------------------------HANDLE NETWORK--------------------------------------------//

void Network::ClientNetwork::handleTCPData(const boost::system::error_code &error, std::size_t recvd_bytes, boost::asio::ip::tcp::socket &tcpsocket)
{
    if (!error && recvd_bytes > 0) {
        if (_data.size() >= (HEADER_SIZE)) {
            header packet = getHeader(_data);
            handleMessageData(packet, _data);
        }
        startAsyncReceiveTCP(tcpsocket);
    } else {
        std::cerr << "Error receiving data: " << error.message() << std::endl;
    }
}

void Network::ClientNetwork::handleNetwork()
{
    _ioService.reset();
    _ioService.poll_one();
}

void Network::ClientNetwork::handleReceive(boost::system::error_code error, std::size_t recvd_bytes)
{
    if (!error && recvd_bytes > 0) {
        while (_data.size() >= HEADER_SIZE) {
            header packet = getHeader(_data);
            handleMessageData(packet, _data);
        }
        // _data.clear();
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
