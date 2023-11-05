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
            ServerTcp(boost::asio::ip::tcp::socket socket, Network::Participants &list,
                int udpPort, std::unordered_map<std::shared_ptr<IServerTcp>, std::pair<int, std::vector<int>>> &_clients, bool &isGame, int &mod);
            ~ServerTcp();
            void start();
            void waitRequest();
            void write(std::string message);
            void connection();
            /**
             * @brief Create a response with a header, a body number and footer
             *
             * @param code RFC code
             * @param entityId id of the entity
             * @return std::string response
             */
            std::string codeLogin(int code, int entityId = -1);
            /**
             * @brief Send 202 to all client
             * @param indexClient index of the new client
            */
            void send202(std::shared_ptr<IServerTcp> participant);
            std::string code401();
            void send201();
            void addClient();
            void removeClient();
        protected:
            void chooseMod();
            int &_typeMod;
            int _udpPort;
            boost::asio::ip::tcp::socket _socket;
            Network::Participants &_list;
            std::unordered_map<std::shared_ptr<IServerTcp>, std::pair<int, std::vector<int>>> &_listClient;
            std::string _data;
            bool &_isGame;
        private:
    };
}
