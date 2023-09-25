/*
** EPITECH PROJECT, 2023
** ServerNetwork.cpp
** File description:
** ServerNetwork
*/

#include "server/network/ServerNetwork.hpp"

Network::ServerNetwork::ServerNetwork(boost::asio::io_service& io_service, int port)
	: _socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
{
	receive();
}

Network::ServerNetwork::~ServerNetwork()
{
}

void Network::ServerNetwork::receive()
{
	_socket.async_receive_from(boost::asio::buffer(_data, 1024), _endpoint,
    [this] (boost::system::error_code error, std::size_t recvd_bytes) {
        if ( !error && recvd_bytes > 0 ) {
            std::cout << "[" << recvd_bytes << "] " << _data << std::endl;
            send();
        }
        else {
            receive();
        }
    });
}

void Network::ServerNetwork::send()
{
	std::string str = "endpoint: ";

	str += _endpoint.address().to_string();
	str += " port ";
	str += std::to_string((int)_endpoint.port());
    _socket.async_send_to(boost::asio::buffer(str.c_str(), str.length()), _endpoint,
	[this] (boost::system::error_code error, std::size_t recvd_bytes) {
	    receive();
	});
}
