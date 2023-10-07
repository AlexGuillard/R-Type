/*
** EPITECH PROJECT, 2023
** ClientNetwork.hpp
** File description:
** ClientNetwork
*/

#ifndef CLIENTNETWORK_HPP_
#define CLIENTNETWORK_HPP_
#include "ANetwork.hpp"
#include <iostream>
#include "Error.hpp"
#include <memory>
#define MAX_SIZE_BUFFER 1024

namespace Network {

    /**
     * @brief Enum used to know the movement of the player on the server
     *
     */
    enum class Movement {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    /**
     * @brief Enum used to know the action of the player on the server
     *
     */
    enum class Action {
        SHOOT,
        DROP
    };
    /**
     *@brief ClientNetwork class use to communicate with the server
     *
     */
    class ClientNetwork : public ANetwork {

    public:
        /**
         * @brief Destroy the Client Network object
         *
         */
        ~ClientNetwork();
        /**
         * @brief This function is used to receive data from the server
         *
         * @param error
         * @param recvd_bytes
         */
        void handleReceive(boost::system::error_code error, std::size_t recvd_bytes);
        /**
         * @brief This function is used to send data to the server
         *
         * @param error
         * @param recvd_bytes
         */
        void handleSend(boost::system::error_code error, std::size_t recvd_bytes);
        /**
         * @brief This function is used to send a hello to the server to connect to it
         *
         */
        void sendHello();
        /**
         * @brief Start the main loop of the client
         *
         */
        void start();
        /**
         * @brief This function is used to send a movement from the player to the server
         *
         * @param movement
         */
        void sendMovement(Movement movement);
        /**
         * @brief This function is used to send an action from the player to the server
         *
         * @param action
         */
        void sendAction(Action action);
        /**
         * @brief This function is used to connect to the server if the server return 301 then the connection and return true else false
         *
         * @param host
         * @param port
         */
        bool connect(const std::string &host, int port);

        /**
         * @brief Get the Instance object
         *
         * @return ClientNetwork&
         */
        static ClientNetwork &getInstance();
        /**
         * @brief Get the Instance object
         *
         * @param io_service
         * @param host
         * @param port
         * @return ClientNetwork&
         */
        static ClientNetwork &getInstance(boost::asio::io_service &io_service, const std::string &host, int port);

    private:
        //Port of the server
        int _port;
        //Host of the server
        std::string _host;
        //Used to manage asynchrous services
        boost::asio::io_service _ioService;
        //Socket of the clientok but
        boost::asio::ip::udp::socket _socket;
        //Data received
        std::string _dataReceived;
        //Buffer used to receive data
        std::array<char, MAX_SIZE_BUFFER> _buffer;
        //Stock class for SingleTon
        static std::unique_ptr<ClientNetwork> instance;

        /**
         * @brief Construct a new Client Network object with parameters
         *
         * @param io_service
         * @param host
         * @param port
         */
        ClientNetwork(boost::asio::io_service &io_service, const std::string &host, int port);
        /**
         * @brief Construct a new Client Network object without parameters
         *
         */
        ClientNetwork();
    };
}

#endif /* !CLIENTNETWORK_HPP_ */
