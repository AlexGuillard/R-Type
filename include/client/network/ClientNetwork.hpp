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

namespace Network {
	/**
	 *@brief ClientNetwork class use to communicate with the server
	 *
	 */
	class ClientNetwork : public ANetwork {

	public:
		/**
		 * @brief Construct a new Client Network object
		 *
		 * @param io_service
		 * @param host
		 * @param port
		 */
		ClientNetwork(boost::asio::io_service &io_service, const std::string &host, int port);
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

	private:
		//Port of the server
		int _port;
		//Host of the server
		std::string _host;
		//Socket of the clientok but
		boost::asio::ip::udp::socket _socket;
		//Data received
		std::string _data;
	};
}

#endif /* !CLIENTNETWORK_HPP_ */
