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
            ServerNetwork(boost::asio::io_service& io_service, int port);
            ~ServerNetwork();
			void handleReceive(boost::system::error_code error, std::size_t recvd_bytes);
			void handleSend(boost::system::error_code error, std::size_t recvd_bytes);
        protected:
			boost::asio::ip::udp::socket _socket;
			std::unordered_map<std::string, boost::asio::ip::udp::endpoint> clients;
        private:
    };
}

#endif /* !SERVERNETWORK_HPP_ */
