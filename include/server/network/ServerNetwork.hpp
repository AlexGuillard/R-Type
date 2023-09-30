/*
** EPITECH PROJECT, 2023
** ServerNetwork.hpp
** File description:
** ServerNetwork
*/

#ifndef SERVERNETWORK_HPP_
    #define SERVERNETWORK_HPP_
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
            void addClient();
			std::string findClient(std::string id) const;
			std::string getActualClient() const;
        protected:
			/**
			 * @brief variable where the client is
			 *
			 */
			boost::asio::ip::udp::socket _socket;
			/**
			 * @brief hmap for the list of client on the server
			 *
			 */
			std::vector<std::string> _clients;
        private:
    };
}

#endif /* !SERVERNETWORK_HPP_ */
