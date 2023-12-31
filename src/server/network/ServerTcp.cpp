/*
** EPITECH PROJECT, 2023
** ServerTcp.cpp
** File description:
** ServerTcp
*/

#include <iostream>

#include "server/network/ServerTcp.hpp"
#include "server/network/sendCode.hpp"

Network::ServerTcp::ServerTcp(boost::asio::ip::tcp::socket socket, Participants &list,
    int udpPort, std::unordered_map<std::shared_ptr<IServerTcp>, std::pair<int, std::vector<int>>> &_clients, bool &isGame, int &mod)
    : _socket(std::move(socket)), _list(list), _udpPort(udpPort), _listClient(_clients), _isGame(isGame), _typeMod(mod)
{
}

Network::ServerTcp::~ServerTcp()
{
}

void Network::ServerTcp::start()
{
    waitRequest();
}

void Network::ServerTcp::chooseMod()
{
    header dataClient = Network::Send::stringToheader(_data);

    if (dataClient.codeRfc == 243 || dataClient.codeRfc == 244 \
    || dataClient.codeRfc == 241 || dataClient.codeRfc == 242) {
        _typeMod = dataClient.codeRfc;
        send201();
        _isGame = true;
    }
}

void Network::ServerTcp::waitRequest()
{
    int res = 0;

    auto self(shared_from_this());
    _data.resize(MAX_SIZE_BUFF);
    _socket.async_read_some(boost::asio::buffer(_data.data(), _data.size()), [this, self](boost::system::error_code error, std::size_t bytes_transferred) {

        if (!error) {
            if (_list.findClient(shared_from_this()) == true) {
                chooseMod();
            } else {
                connection();
            }
            _data.clear();
            waitRequest();
        } else {
            _data.clear();
            if ((boost::asio::error::eof != error) &&
            (boost::asio::error::connection_reset != error)) {
                waitRequest();
            } else {
                if (_list.findClient(shared_from_this())) {
                    removeClient();
                    _list.leave(shared_from_this());
                    for (int i = 0; i < _list.size(); i++) {
                        _list.getClient(i)->write(codeLogin(200, i));
                    }
                }
            }
        }
    });
}

void Network::ServerTcp::write(std::string message)
{
    auto self(shared_from_this());
    _socket.async_write_some(boost::asio::buffer(message.data(), message.size()),
    [this, self](boost::system::error_code error, std::size_t /*length*/)
    {
        if (!error) {
            waitRequest();
        } else {
            removeClient();
            _list.leave(shared_from_this());
            for (int i = 0; i < _list.size(); i++) {
                _list.getClient(i)->write(codeLogin(200, i));
            }
        }
    });
}

void Network::ServerTcp::connection()
{
    header number = Network::Send::stringToheader(_data);
    header typeMod = Network::Send::stringToheader(_data);
    std::string actualClient;

    std::cout << number.codeRfc << std::endl;
    if (number.codeRfc == CONNECTION_NB && typeMod.codeRfc == 204 && _list.size() < 4 && _isGame == false) {
        int idNewClient = _list.size();
        _list.join(shared_from_this());
        addClient();
        write(codeLogin(200, idNewClient));
        send202(shared_from_this());
    } else if (number.codeRfc == CONNECTION_NB && typeMod.codeRfc == 203 && _list.size() < 1  && _isGame == false) {
        int idNewClient = _list.size();
        _list.join(shared_from_this());
        addClient();
        write(codeLogin(200, idNewClient));
        _typeMod = 241;
        send201();
        _isGame = true;
    } else {
        write(code401());
    }
}

std::string Network::ServerTcp::codeLogin(int code, int entityId)
{
    std::string res;

    res = Network::Send::makeHeader(code, entityId);
    res.append(Network::Send::makeBodyNum(entityId + 1));
    res.append(Network::Send::makeBodyNum(code));
    return res;
}

void Network::ServerTcp::send202(std::shared_ptr<IServerTcp> participant)
{
    for (int i = 0; i < _list.size(); i++) {
        if (_list.getClient(i) == participant) {
            continue;
        }
        _list.getClient(i)->write(codeLogin(202, 0));
    }
}

std::string Network::ServerTcp::code401()
{
    std::string res;

    res = Network::Send::makeHeader(401, -1);
    res.append(Network::Send::makeBodyNum(401));
    return res;
}

void Network::ServerTcp::send201()
{
    std::string res;

    res = Network::Send::makeHeader(201, -1);
    res.append(Network::Send::makeBodyNum(_udpPort));
    res.append(Network::Send::makeBodyNum(201));
    for (int i = 0; i < _list.size(); i++) {
        _list.getClient(i)->write(res);
    }
}

void Network::ServerTcp::addClient()
{
    std::string actualClient;

    actualClient = _socket.remote_endpoint().address().to_string() + ":" + std::to_string(_socket.remote_endpoint().port());
    _listClient[shared_from_this()].first = _listClient.size();
}

void Network::ServerTcp::removeClient()
{
    _listClient.erase(shared_from_this());
}
