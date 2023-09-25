/*
** EPITECH PROJECT, 2023
** ServerNetwork.hpp
** File description:
** ServerNetwork
*/

#ifndef SERVERNETWORK_HPP_
    #define SERVERNETWORK_HPP_
    #include "ANetwork.hpp"

namespace Network {
    class ServerNetwork : public ANetwork {
        public:
            ServerNetwork(std::string hostname, int port);
            ~ServerNetwork();
        protected:
			asio::io_context io_context;
			asio::ip::udp::socket _socket;
        private:
    };
}

#endif /* !SERVERNETWORK_HPP_ */
