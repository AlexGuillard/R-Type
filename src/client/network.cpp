/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** network
*/

#include "client/network.hpp"
#include "client/network/ClientNetwork.hpp"
#include "GameEngine/Events.hpp"

namespace Network {

    bool startClientNetwork(const std::string &host, int port)
    {
        //TODO:
        //connect return a bool to let us know if the connection was successful or not
        std::cout << "Connecting to " << host << ":" << port << std::endl;
        return ClientNetwork::getInstance().connect(host, port);
    }

    void updateClientNetwork()
    {
        GameEngine::Events::Type type;
        ClientNetwork &clientNetwork = ClientNetwork::getInstance();

        clientNetwork.asyncReceive(Network::ClientNetwork::getInstance().getSocket());
        clientNetwork.handleNetwork();
        while (GameEngine::Events::poll(type)) {
            switch (type) {
            case GameEngine::Events::Type::PLAYER_UP:
                clientNetwork.sendMovement(Network::Movement::UP);
                break;
            case GameEngine::Events::Type::PLAYER_DOWN:
                clientNetwork.sendMovement(Network::Movement::DOWN);
                break;
            case GameEngine::Events::Type::PLAYER_LEFT:
                clientNetwork.sendMovement(Network::Movement::LEFT);
                break;
            case GameEngine::Events::Type::PLAYER_RIGHT:
                clientNetwork.sendMovement(Network::Movement::RIGHT);
                break;
            case GameEngine::Events::Type::PLAYER_SHOOT:
                clientNetwork.sendAction(Network::Action::SHOOT);
                break;
            case GameEngine::Events::Type::PLAYER_DROP:
                clientNetwork.sendAction(Network::Action::DROP);
                break;
            default:
                break;
            }
        }
    }

    void stopClientNetwork()
    {
        Network::ClientNetwork::getInstance().stopIOService();
    }
}