/*
** EPITECH PROJECT, 2023
** ServerNetwork.hpp
** File description:
** ServerNetwork
*/

#pragma once

#include <iostream>
#include <algorithm>

#include "ANetwork.hpp"

namespace Network {
    /**
     * @brief Network class for server
     *
     */
    class ServerNetwork : public ANetwork {
        public:
            ServerNetwork(boost::asio::io_service& io_service, int port);
            ~ServerNetwork();
            void tcpConnection();
            void udpConnection();
            // handler for asynd accept in tcp connection
            void acceptHandler(const boost::system::error_code& error);
            /**
             * @brief function called after receiving data
             *
             * @param error empty if finish with no error
             * @param recvd_bytes number of bytes received
             */
            void handleReceive(boost::system::error_code error, std::size_t recvd_bytes);
            /**
             * @brief function called after sending data
             *
             * @param error empty if finish with no error
             * @param recvd_bytes number of bytes received
             */
            void handleSend(boost::system::error_code error, std::size_t recvd_bytes);
            /**
             * @brief add a client in vector of clients if it fills conditions
             *
             */
            void addClient();
            /**
             * @brief find a client in the vector by sending a id, if can not find, return ""
             *
             * @param id
             * @return std::string
             */
            std::string findClient(std::string id) const;
            /**
             * @brief function that update game when tick is finish
             *
             */
            void updateTicks();
            /**
             * @brief Get the Actual Client id
             *
             * @return std::string
             */
            std::string getActualClient() const;
            /**
             * @brief see if client have a good connection on the server, the server repond then with 200 or 401
             *
             */
            void connection();
        protected:
            // store the io_service
            boost::asio::io_service &_ioService;
            /**
             * @brief variable where the client is
             *
             */
            boost::asio::ip::udp::socket _asyncSocket;
            /**
             * @brief hmap for the list of client on the server
             *
             */
            std::vector<std::string> _clients;
            // variable for the timer and the ticks
            boost::asio::deadline_timer _timer;
            bool isGame = false;
            // list of sockets for potential clients
            std::vector<boost::asio::ip::tcp::socket> _socket;
            // necessary for acceptation tcp clients
            boost::asio::ip::tcp::acceptor _acceptor;
        private:
    };
}
