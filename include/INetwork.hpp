/*
** EPITECH PROJECT, 2023
** INetwork.hpp
** File description:
** INetwork
*/

#ifndef INETWORK_HPP_
    #define INETWORK_HPP_
	#include <boost/asio.hpp>

namespace Network {
	enum Size {
		MAX_SIZE_BUFF = 1024,
	};
    class INetwork {
        public:
            virtual ~INetwork() = default;
			virtual void receive(boost::asio::ip::udp::socket &_socket) = 0;
			virtual void send(boost::asio::ip::udp::socket &_socket, std::string str) = 0;
			virtual void handleReceive(boost::system::error_code error, std::size_t recvd_bytes) = 0;
			virtual void handleSend(boost::system::error_code error, std::size_t recvd_bytes) = 0;
    };
}

#endif /* !INETWORK_HPP_ */
