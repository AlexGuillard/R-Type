/*
** EPITECH PROJECT, 2023
** ServerNetwork.hpp
** File description:
** ServerNetwork
*/

#pragma once

#include <iostream>
#include <algorithm>
#include <thread>
#include <memory>

#include "ANetwork.hpp"
#include "server/network/Participants.hpp"
#include "server/network/ServerTcp.hpp"
#define TICKS_UPDATE 200

namespace Network {
    enum class Connection {
        CONNECTED,
        NOT_CONNECTED
    };
    /**
     * @brief Network class for server
     *
     */
    class ServerNetwork : public ANetwork {
        public:
            ServerNetwork(boost::asio::io_service& io_service, int portTcp, int portUdp);
            ~ServerNetwork();
            /**
             * @brief used when making the connections from the clients
             *
             */
            void tcpConnection();
            /**
             * @brief used when going into the game
             *
             */
            void udpConnection();
            // handler for asynd accept in tcp connection
            void acceptHandler(const boost::system::error_code& error, boost::asio::ip::tcp::socket socket);
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
        protected:
            // int for udp port to send when tcp connection
            int _portUdp;
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
            std::unordered_map<std::string, std::pair<int, std::vector<int>>> _clients;
            // variable for the timer and the ticks
            boost::asio::deadline_timer _timer;
            // necessary for acceptation tcp clients
            boost::asio::ip::tcp::acceptor _acceptor;
            // counter for ticks in game
            std::size_t _tickCount = 0;
            // boolean to check if we are on game or not
            bool _isGame = false;
        private:
            Participants _list;
            /**
             * @brief Set the Udp Socket object
             *
             * @param port port for udp to listen to
             * @return int
             */
            int setUdpSocket(int port);
            /**
             * @brief Set the Tcp Socket object
             *
             * @param port port for udp to listen to
             * @return int
             */
            int setTcpSocket(int port);
            void handleClientData(int num);
    };
}
