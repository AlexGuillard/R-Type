/*
** EPITECH PROJECT, 2023
** ServerNetwork.hpp
** File description:
** ServerNetwork
*/

#ifndef SERVERNETWORK_HPP_
    #define SERVERNETWORK_HPP_
	#include <iostream>
    #include "ANetwork.hpp"

namespace Network {
    class ServerNetwork : public ANetwork {
        public:
            ServerNetwork(std::string hostname, int port);
            ~ServerNetwork();
			void receive();
			static void handle(const asio::error_code& error, std::size_t bytes_transferred);
        protected:
			asio::io_context io_context;
			asio::ip::udp::socket _socket;
			asio::ip::udp::endpoint _endpoint;
			char *_data[1024];
        private:
    };
}

#endif /* !SERVERNETWORK_HPP_ */
