/*
** EPITECH PROJECT, 2023
** INetwork.hpp
** File description:
** INetwork
*/

#pragma once

#include <boost/asio.hpp>

namespace Network {
    /**
     * @brief enum for max size of the buffer for the data
     *
     */
    enum Size {
        MAX_SIZE_BUFF = 1024,
    };
    /**
     * @brief interface of the network
     *
     */
    class INetwork {
    public:
        virtual ~INetwork() = default;
        /**
         * @brief function to call when you want to receive informations
         *
         * @param _socket variable where you listening
         */
        virtual void receive(boost::asio::ip::udp::socket &_socket) = 0;
        /**
         * @brief function to call when you want to send informations
         *
         * @param _socket variable where you send
         * @param str string for message to send
         */
        virtual void send(boost::asio::ip::udp::socket &_socket, std::string str) = 0;
        /**
         * @brief function called after receiving data
         *
         * @param error empty if finish with no error
         * @param recvd_bytes number of bytes received
         */
        virtual void handleReceive(boost::system::error_code error, std::size_t recvd_bytes) = 0;
        /**
         * @brief function called after sending data
         *
         * @param error empty if finish with no error
         * @param recvd_bytes number of bytes received
         */
        virtual void handleSend(boost::system::error_code error, std::size_t recvd_bytes) = 0;
    };
}
