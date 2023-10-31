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
#include "constants.hpp"
#include "ECS/Components/HPComponent.hpp"

Network::ServerNetwork::ServerNetwork(boost::asio::io_service &io_service, int portTCP, int portUdp)
    : _ioService(std::ref(io_service)), _acceptor(_ioService), _asyncSocket(_ioService),
    _timer(io_service), _portUdp(portUdp),
    _engine(GameEngine::createServerEngine(std::bind(&Network::ServerNetwork::serverEventHandler, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)))
{
    _stage = 1;
    boost::asio::ip::tcp::resolver resolver(_ioService);
    boost::asio::ip::tcp::resolver::query query(boost::asio::ip::host_name(), "");
    boost::asio::ip::tcp::resolver::iterator endpoints = resolver.resolve(query);

    portTCP = setTcpSocket(portTCP);
    if (portTCP == -1)
        throw std::runtime_error("Can not set server tcp");
    _portUdp = setUdpSocket(portUdp);
    if (_portUdp == -1)
        throw std::runtime_error("Can not set server udp");
    _script.openLVL(_stage);
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

void Network::ServerNetwork::updateGame()
{
    _tickCount++;
    // host:ip -> {id, [RFC, ...]}
    for (auto &&[client, data] : _ids) {
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
        data.second.clear();
    }
    auto &&teams = _engine.getRegistry(GameEngine::registryTypeEntities).getComponents<ECS::Components::TeamComponent>();
    bool allyAlive = false;
    for (const auto &ide : teams) {
        if (ide.has_value() && ide->team == Enums::TeamGroup::ALLY) {
            allyAlive = true;
            break;
        }
    }
    if (allyAlive == true) {
        if (_engine._listIdBoss.size() > 0) {
            for (int i = 0; i < _engine._listIdBoss.size(); i++) {
                if (!_engine.getRegistry(GameEngine::registryTypeEntities).getComponents<ECS::Components::HPComponent>().at(_engine._listIdBoss[i])) {
                    _stage += 1;
                    _tickCount = 0;
                    if (_script.openLVL(_stage) == 0) {
                        _dataToSend.append(Send::makeHeader(221, 0));
                        _dataToSend.append(Send::makeBodyNum(221));
                    } else {
                        _dataToSend.append(Send::makeHeader(231, _stage));
                        _dataToSend.append(Send::makeBodyNum(231));
                    }
                    _engine._listIdBoss.clear();
                    break;
                }
            }
        }
    } else {
        std::cout << "all dead" << std::endl;
        _dataToSend.append(Send::makeHeader(222, 0));
        _dataToSend.append(Send::makeBodyNum(222));
    }
    _engine.run();
    if (_tickCount > 2) {
        sendClientEntities();
    }
}

void Network::ServerNetwork::sendClientEntities()
{
    auto &&dataPositions = _engine.getRegistry(GameEngine::registryTypeEntities).getComponents<ECS::Components::PositionComponent>();
    auto &&dataVelocity = _engine.getRegistry(GameEngine::registryTypeEntities).getComponents<ECS::Components::VelocityComponent>();
    std::string res = "";

    for (int i = 0; i < dataPositions.size(); i++) {
        if (dataPositions[i].has_value()) {
            _dataToSend.append(Send::makeHeader(331, i));
            _dataToSend.append(Send::makeBodyPosition(dataPositions[i].value()));
            if (dataVelocity[i].has_value()) {
                _dataToSend.append(Send::makeBodyVelocity(dataVelocity[i].value()));
            } else {
                _dataToSend.append(Send::makeBodyVelocity(static_cast<ECS::Components::VelocityComponent>(0, 0)));
            }
            _dataToSend.append(Send::makeBodyNum(_tickCount));
            _dataToSend.append(Send::makeBodyNum(331));
        }
    }
    for (const auto& pair : _listUdpEndpoints) {
        const boost::asio::ip::udp::endpoint& endpoint = pair.second;
        _asyncSocket.send_to(boost::asio::buffer(_dataToSend.c_str(), _dataToSend.length()) , endpoint);
    }
    _dataToSend.clear();
}

void Network::ServerNetwork::updateTicks()
{
    _timer.expires_from_now(boost::posix_time::millisec(Constants::tickUpdate));
    _timer.async_wait([this](const boost::system::error_code &error) {
        std::vector<Info> scriptInfo;
        if (error) {
            std::cerr << "_timer error: " << error.message() << std::endl;
            updateTicks();
            return;
        }
        if (_canPlay) {
            scriptInfo = _script.getTickScript(_tickCount);
            if (!scriptInfo.empty()) {
                SendClientsInfo(scriptInfo);
            }
            updateGame();
        }
        updateTicks();
    });
}

void Network::ServerNetwork::handleReceive(boost::system::error_code error, std::size_t recvd_bytes)
{
    std::string actualClient;
    const size_t maxNbClients = 5;

    if (!error && recvd_bytes > 0) {
        header dataClient = Send::stringToheader(_data);
        if (findClient(dataClient) && _canPlay == true) {
            handleClientData(dataClient.codeRfc);
        } else {
            if (_canPlay == true) {
                asyncSend(_asyncSocket, "need tcp connection first\n");
            }
        }
        _data.clear();
    }
    asyncReceive(_asyncSocket);
}

std::string Network::ServerNetwork::getActualClient() const
{
    return _endpoint.address().to_string() + ":" + std::to_string(_endpoint.port());
}

bool Network::ServerNetwork::findClient(Network::header clientData)
{
    if (clientData.entity >= 0 && clientData.entity <= 4 && clientData.codeRfc == 217) {
        _listUdpEndpoints[getActualClient()] = _endpoint;
        _ids[getActualClient()].first = clientData.entity;
        if (_listUdpEndpoints.size() == _clients.size() && _canPlay == false && _isGame) {
            _canPlay = true;
            SendClientsPlay();
        }
        return true;
    } else if (_listUdpEndpoints.size() == _clients.size()) {
        return true;
    }
    return false;
}

void Network::ServerNetwork::handleSend(boost::system::error_code error, std::size_t recvd_bytes)
{
    if (error) {
        std::cerr << "Error sending data: " << error.message() << std::endl;
    }
    asyncReceive(_asyncSocket);
}

bool Network::ServerNetwork::isGameRunning() const
{
    return this->_canPlay;
}

void Network::ServerNetwork::update()
{
    _ioService.poll();
    _ioService.reset();
}

void Network::ServerNetwork::handleClientData(int num)
{
    if (num >= 210 && num <= 216) {
        if (_ids.count(getActualClient())) {
            _ids[getActualClient()].second.push_back(num);
        }
    }
}

void Network::ServerNetwork::SpawnMob(Info script)
{
    auto &&registry = _engine.getRegistry(GameEngine::registryTypeEntities);
    const int x = Constants::cameraDefaultWidth - 10;

    if (script.rfc >= 301 && script.rfc <= 307) {
        ECS::Entity entity = registry.spawnEntity();
        switch (script.rfc) {
            case 301:
                ECS::Creator::createEnemyBasic(registry, entity, x, script.y);
                break;
            case 302:
                ECS::Creator::createBink(registry, entity, x, script.y);
                break;
            case 303:
                ECS::Creator::createScant(registry, entity, x, script.y);
                break;
            case 304:
                ECS::Creator::createBug(registry, entity, x, script.y);
                break;
            case 305:
                ECS::Creator::createCancer(registry, entity, x, script.y);
                break;
            case 306:
                ECS::Creator::createBlaster(registry, entity, x, script.y);
                break;
            case 307:
                _engine._listIdBoss.push_back(entity);
                ECS::Creator::createDobkeratops(registry, entity, x, script.y);
                break;
            default:
                break;
        }
        _dataToSend.append(Send::makeHeader(script.rfc, entity));
        _dataToSend.append(Send::makeBodyMob(x, script.y, script.extra.side));
        _dataToSend.append(Send::makeBodyNum(script.rfc));
    }
}

void Network::ServerNetwork::SendClientsInfo(std::vector<Info> scriptInfo)
{
    for (int i = 0; i < scriptInfo.size(); i++) {
        SpawnMob(scriptInfo[i]);
    }
}

void Network::ServerNetwork::SendClientsPlay()
{
    std::string res = "";
    Enums::PlayerColor color;
    int index = 0;
    auto &&registry = _engine.getRegistry(GameEngine::registryTypeEntities);

    for (auto &allIds : _ids) {
        if (index == 0)
            color = Enums::PlayerColor::CYAN_COLOR;
        else if (index == 1)
            color = Enums::PlayerColor::PURPLE_COLOR;
        else if (index == 2)
            color = Enums::PlayerColor::LIME_COLOR;
        else if (index == 3)
            color = Enums::PlayerColor::RED_COLOR;
        else
            color = Enums::PlayerColor::BLUE_COLOR;
        ECS::Entity entity = registry.entityFromIndex(allIds.second.first);
        const int x = Constants::cameraDefaultWidth / 5;
        const int y = Constants::cameraDefaultHeight / (_ids.size() + 1) * (index + 1);
        ECS::Creator::createAlly(registry, entity, x, y, color);
        for (const auto& pair : _listUdpEndpoints) {
            res.clear();
            const boost::asio::ip::udp::endpoint& endpoint = pair.second;
            if (pair.first == allIds.first) {
                res = Send::makeHeader(311, entity);
                res.append(Send::makeBodyAlly(x, y, color));
                res.append(Send::makeBodyNum(311));
            } else {
                res = Send::makeHeader(312, entity);
                res.append(Send::makeBodyAlly(x, y, color));
                res.append(Send::makeBodyNum(312));
            }
            for (int i = 0; i < 10; i++)
                _asyncSocket.send_to(boost::asio::buffer(res.c_str(), res.length()) , endpoint);
        }
        index++;
    }
}
