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
            ClientNetwork(int port, std::string machine);
            ~ClientNetwork() override;
			void send(const std::string& message) override;

        private:
			int _port;
			std::string _host;
			int _fdClient;
    };
}

#endif /* !CLIENTNETWORK_HPP_ */
