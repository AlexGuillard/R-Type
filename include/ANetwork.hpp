/*
** EPITECH PROJECT, 2023
** ANetwork.hpp
** File description:
** ANetwork
*/

#pragma once

#include <iostream>
#include <vector>

#include "INetwork.hpp"

namespace Network {
    /**
     * @brief abstract class of INetwork
     *
     */
    class ANetwork : public INetwork {
        public:
            virtual ~ANetwork() = default;
            /**
             * @brief function to call when you want to receive informations
             *
             * @param _socket variable where you listening
             */
            void asyncReceive(boost::asio::ip::udp::socket &_socket);
            /**
             * @brief function to call when you want to send informations
             *
             * @param _socket variable where you send
             */
            void asyncSend(boost::asio::ip::udp::socket &_socket, std::string str);
            /**
             * @brief function to call when you want to receive informations
             *
             * @param _socket variable where you listening
             */
            void receive(boost::asio::ip::tcp::socket &_socket);
            /**
             * @brief function to call when you want to send informations
             *
             * @param _socket variable where you send
             */
            void send(boost::asio::ip::tcp::socket &_socket, std::string str);
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
        protected:
            /**
             * @brief variable that contain what you received
             *
             */
            std::string _data;
            /**
             * @brief contain the IP address and a protocol port number
             *
             */
            boost::asio::ip::udp::endpoint _endpoint;
        private:
    };
}
