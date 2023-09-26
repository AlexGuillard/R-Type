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

namespace Network {
    class ClientNetwork : public ANetwork  {
        public:
            ClientNetwork();
            ~ClientNetwork();
			void handleReceive(boost::system::error_code error, std::size_t recvd_bytes);
			void handleSend(boost::system::error_code error, std::size_t recvd_bytes);
        protected:
        private:
			int _port;
			std::string _host;
			int _fdClient;
    };
}

#endif /* !CLIENTNETWORK_HPP_ */
