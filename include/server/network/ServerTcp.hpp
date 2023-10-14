/*
** EPITECH PROJECT, 2023
** ServerTcp.hpp
** File description:
** ServerTcp
*/

#pragma once
#include "server/network/IServerTcp.hpp"
#include "server/network/Participants.hpp"

namespace Network {
    class ServerTcp : public IServerTcp,
    public std::enable_shared_from_this<ServerTcp> {
        public:
            ServerTcp(boost::asio::ip::tcp::socket socket, Network::Participants &list, int udpPort);
            ~ServerTcp();
            void start();
            void waitRequest();
            void write(std::string message);
            void connection();
            std::string codeLogin(int code);
            void send202(int indexClient);
            std::string code401();
            void send201();
        protected:
            int _udpPort;
            boost::asio::ip::tcp::socket _socket;
            Network::Participants &_list;
            std::string _data;
        private:
    };
}
