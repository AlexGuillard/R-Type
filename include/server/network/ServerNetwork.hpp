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
#include "GameEngine/GameEngine.hpp"
#define TICKS_UPDATE 200

namespace Network {
    /**
     * @brief Network class for server
     *
     */
    class ServerNetwork : public ANetwork {
    public:
        ServerNetwork(boost::asio::io_service &io_service, int portTcp, int portUdp);
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
        /**
         * @brief used to wait read of tcp socket
         *
         * @param socket client socket that send data
         */
        void waitRequest(std::shared_ptr<boost::asio::ip::tcp::socket> &socket);
        // handler for asynd accept in tcp connection
        void acceptHandler(const boost::system::error_code &error, boost::asio::ip::tcp::socket socket);
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
        void setGameEngine(std::shared_ptr<GameEngine::GameEngine> &engine);
        // TODO: Replace with actual implementation
        std::unordered_map<std::string, std::pair<int, std::vector<int>>> getClientInputs();
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
         * @brief Get the Actual Client id
         *
         * @param socket tcp socket of client
         * @return std::string
         */
        std::string getActualClient(boost::asio::ip::tcp::socket &socket) const;
        /**
         * @brief see if client have a good connection on the server, the server repond then with 200 or 401
         *
         */
        void connection(std::shared_ptr<boost::asio::ip::tcp::socket> &socket);
        /**
         * @returns True if the game is running, false otherwise
        */
        bool isGameRunning() const;
        /**
         * @brief Runs the io service of asio
        */
        void run(GameEngine::GameEngine &engine);
    protected:
        // int for udp port to send when tcp connection
        int portUdp;
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
        // boolean to change from tcp to udp and vice versa
        bool isGame = false;
        // list of sockets for potential clients
        std::vector<std::shared_ptr<boost::asio::ip::tcp::socket>> _socket;
        // necessary for acceptation tcp clients
        boost::asio::ip::tcp::acceptor _acceptor;
        // lists of accepted clients
        std::vector<std::shared_ptr<boost::asio::ip::tcp::socket>> _clientsTcp;
    private:
        /**
         * @brief write a login code (202 or 200)
         *
         * @param code the code sended in the header and the footer
         * @return std::string
         */
        std::string codeLogin(int code);
        /**
         * @brief string for 401 error for client
         *
         * @return std::string
         */
        std::string code401();
        /**
         * @brief send a login of a new client to every client
         *
         * @param indexClient index of the new client in _clientsTcp
         */
        void send202(int indexClient);
        /**
         * @brief send to clients to pass in udp mod
         *
         */
        void send201();
        std::shared_ptr<GameEngine::GameEngine> _engine;
    };
}
