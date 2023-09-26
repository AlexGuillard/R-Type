/*
** EPITECH PROJECT, 2023
** ANetwork.hpp
** File description:
** ANetwork
*/

#ifndef ANETWORK_HPP_
    #define ANETWORK_HPP_
    #include "INetwork.hpp"

namespace Network {
    class ANetwork : public INetwork {
        public:
            virtual ~ANetwork() = default;
			void receive(boost::asio::ip::udp::socket &_socket);
			void send(boost::asio::ip::udp::socket &_socket, std::string str);
			virtual void handleReceive(boost::system::error_code error, std::size_t recvd_bytes) = 0;
			virtual void handleSend(boost::system::error_code error, std::size_t recvd_bytes) = 0;
        protected:
			char _data[MAX_SIZE_BUFF];
			boost::asio::ip::udp::endpoint _endpoint;
        private:
    };
}

#endif /* !ANETWORK_HPP_ */
