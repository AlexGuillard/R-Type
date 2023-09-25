/*
** EPITECH PROJECT, 2023
** ServerNetwork.hpp
** File description:
** ServerNetwork
*/

#ifndef SERVERNETWORK_HPP_
    #define SERVERNETWORK_HPP_
	#include <iostream>
	#include <boost/asio.hpp>
    #include "ANetwork.hpp"

namespace Network {
    class ServerNetwork : public ANetwork {
        public:
            ServerNetwork(boost::asio::io_service& io_service, int port);
            ~ServerNetwork();
			void receive();
			void send();
			// static void handle(const asio::error_code& error, std::size_t bytes_transferred);
        protected:
			boost::asio::ip::udp::socket _socket;
			boost::asio::ip::udp::endpoint _endpoint;
			char _data[1024];
        private:
    };
}

#endif /* !SERVERNETWORK_HPP_ */
