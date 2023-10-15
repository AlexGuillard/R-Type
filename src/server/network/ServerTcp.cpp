/*
** EPITECH PROJECT, 2023
** ServerTcp.cpp
** File description:
** ServerTcp
*/

#include "server/network/ServerTcp.hpp"
#include "server/network/sendCode.hpp"

Network::ServerTcp::ServerTcp(boost::asio::ip::tcp::socket socket, Participants &list,
    int udpPort, std::unordered_map<std::string, std::pair<int, std::vector<int>>> &_clients, bool &isGame)
    : _socket(std::move(socket)), _list(list), _udpPort(udpPort), _listClient(_clients), _isGame(isGame)
{
}

Network::ServerTcp::~ServerTcp()
{
}

void Network::ServerTcp::start()
{
    waitRequest();
}

void Network::ServerTcp::waitRequest()
{
    int res = 0;

    auto self(shared_from_this());
    _data.resize(MAX_SIZE_BUFF);
    _socket.async_read_some(boost::asio::buffer(_data.data(), _data.size()), [this, self](boost::system::error_code error, std::size_t bytes_transferred) {
        header dataClient;

        if (!error) {
            if (_list.findClient(shared_from_this()) == true) {
                dataClient = Network::Send::stringToheader(_data);
                std::cout << "[" << bytes_transferred << "] " << dataClient.codeRfc << " from " << _socket.remote_endpoint().address() << std::endl;
                if (dataClient.codeRfc == 201) {
                    send201();
                    _isGame = true;
                }
            } else {
                connection();
            }
            _data.clear();
            waitRequest();
        } else {
            if ((boost::asio::error::eof != error) &&
            (boost::asio::error::connection_reset != error)) {
                waitRequest();
            } else {
                _list.leave(shared_from_this());
                removeClient();
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
            _list.leave(shared_from_this());
            removeClient();
        }
    });
}

void Network::ServerTcp::connection()
{
    header number = Network::Send::stringToheader(_data);
    std::string actualClient;

    std::cout << number.codeRfc << std::endl;
    if (number.codeRfc == CONNECTION_NB && _list.size() < 4) {
        _list.join(shared_from_this());
        addClient();
        write(codeLogin(200));
        send202(_list.size());
    } else {
        write(code401());
    }
}

std::string Network::ServerTcp::codeLogin(int code)
{
    std::string res;

    res = Network::Send::makeHeader(code, _list.size() - 1);
    res.append(Network::Send::makeBodyNum(_list.size()));
    res.append(Network::Send::makeBodyNum(code));
    return res;
}

void Network::ServerTcp::send202(int indexClient)
{
    for (int i = 0; i < _list.size(); i++) {
        _list.getClient(i)->write(codeLogin(202));
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

std::string Network::ServerTcp::getActualClient()
{
    return _socket.remote_endpoint().address().to_string() + ":" + std::to_string(_socket.remote_endpoint().port());
}

void Network::ServerTcp::addClient()
{
    std::string actualClient;

    actualClient = _socket.remote_endpoint().address().to_string() + ":" + std::to_string(_socket.remote_endpoint().port());
    _listClient[actualClient].first = _listClient.size();
}

void Network::ServerTcp::removeClient()
{
    _listClient.erase(getActualClient());
}
