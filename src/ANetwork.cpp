/*
** EPITECH PROJECT, 2023
** aNetwork.cpp
** File description:
** ANetwork
*/

#include "ANetwork.hpp"

void Network::ANetwork::receive(boost::asio::ip::udp::socket &_socket)
{
	_data.resize(MAX_SIZE_BUFF);
    _socket.async_receive_from(
        boost::asio::buffer(_data.data(), _data.size()), _endpoint,
        std::bind(&Network::ANetwork::handleReceive, this,
                    std::placeholders::_1, std::placeholders::_2));
}

void Network::ANetwork::send(boost::asio::ip::udp::socket &_socket, std::string str)
{
    _socket.async_send_to(
        boost::asio::buffer(str.c_str(), str.length()), _endpoint,
        std::bind(&Network::ANetwork::handleSend, this,
                    std::placeholders::_1, std::placeholders::_2));
}
