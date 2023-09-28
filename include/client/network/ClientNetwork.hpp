/*
** EPITECH PROJECT, 2023
** ClientNetwork.hpp
** File description:
** ClientNetwork
*/

#ifndef CLIENTNETWORK_HPP_
#define CLIENTNETWORK_HPP_
#include "ANetwork.hpp"

namespace Network {
	class ClientNetwork : public ANetwork {
	public:
		ClientNetwork();
		~ClientNetwork();
		void handleReceive(boost::system::error_code error, std::size_t recvd_bytes);
		void handleSend(boost::system::error_code error, std::size_t recvd_bytes);
	protected:
	private:
	};
}

#endif /* !CLIENTNETWORK_HPP_ */
