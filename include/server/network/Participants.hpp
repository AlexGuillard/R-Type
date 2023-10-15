/*
** EPITECH PROJECT, 2023
** Participants.hpp
** File description:
** Participants
*/

#pragma once
#include <set>
#include "server/network/IServerTcp.hpp"

namespace Network {
    class Participants {
        public:
        void join(std::shared_ptr<IServerTcp> participant);
        void leave(std::shared_ptr<IServerTcp> participant);
        int size();
        bool findClient(std::shared_ptr<IServerTcp> client);
        std::shared_ptr<IServerTcp> getClient(int index);
        private:
            std::set<std::shared_ptr<IServerTcp>> _participants;
    };
}
