/*
** EPITECH PROJECT, 2023
** Participants
** File description:
** Participants
*/

#include "server/network/Participants.hpp"

void Network::Participants::join(std::shared_ptr<IServerTcp> participant)
{
    _participants.insert(participant);
}

void Network::Participants::leave(std::shared_ptr<IServerTcp> participant)
{
    _participants.erase(participant);
}

int Network::Participants::size()
{
    return _participants.size();
}

bool Network::Participants::findClient(std::shared_ptr<IServerTcp> client)
{
    auto res = _participants.find(client);
    return res != _participants.end();
}

std::shared_ptr<Network::IServerTcp> Network::Participants::getClient(int index)
{
    auto itParticipants = _participants.begin();
    int cout = 0;

    for (; itParticipants != _participants.end(); itParticipants++) {
        if (cout == index)
            return *itParticipants;
        cout++;
    }
    return nullptr;
}
