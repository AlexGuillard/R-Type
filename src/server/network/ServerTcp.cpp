/*
** EPITECH PROJECT, 2023
** ServerTcp.cpp
** File description:
** ServerTcp
*/

#include "server/network/ServerTcp.hpp"
#include "server/network/sendCode.hpp"

Network::ServerTcp::ServerTcp(boost::asio::ip::tcp::socket socket, Participants &list, int udpPort) : _socket(std::move(socket)), _list(list), _udpPort(udpPort)
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
        int number = 0;

        if (!error) {
            if (_list.findClient(shared_from_this()) == true) {
                number = Network::Send::stringToInt(_data);
                std::cout << "[" << bytes_transferred << "] " << number << "from" << _socket.remote_endpoint().address() << std::endl;
                if (number == 201) {
                    send201();
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
                std::cout << "list before" << _list.size() << std::endl;
                _list.leave(shared_from_this());
                std::cout << "list after" << _list.size() << std::endl;
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
        if (!error)
        {
            waitRequest();
        }
        else
        {
            _list.leave(shared_from_this());
        }
    });
}

void Network::ServerTcp::connection()
{
    int number = Network::Send::stringToInt(_data);
    std::string actualClient;

    std::cout << number << std::endl;
    if (number == CONNECTION_NB && _list.size() < 4) {
        _list.join(shared_from_this());
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
    res.append(Network::Send::makeBinaryInt(_list.size()));
    res.append(Network::Send::makeBinaryInt(code));
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
    res.append(Network::Send::makeBinaryInt(401));
    return res;
}

void Network::ServerTcp::send201()
{
    std::string res;

    res = Network::Send::makeHeader(201, -1);
    res.append(Network::Send::makeBinaryInt(_udpPort));
    res.append(Network::Send::makeBinaryInt(201));
    for (int i = 0; i < _list.size(); i++) {
        _list.getClient(i)->write(res);
    }
}
