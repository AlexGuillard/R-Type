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

    bool returnIsCoUDP()
    {
        return isCoUDP;
    }

    bool startClientNetwork(const std::string &host, int tcpPort, int udpPort, Network::ConnectionType type, GameEngine::GameEngine &engine)
    {
        //TODO:
        //connect return a bool to let us know if the connection was successful or not
        if (type == Network::ConnectionType::TCP) {
            std::cout << "Connecting TCP " << host << ":" << tcpPort << std::endl;
            return ClientNetwork::getInstance(engine).connect(host, tcpPort, true);
        } else {
            std::cout << "Connecting UDP " << host << ":" << udpPort << std::endl;
            return ClientNetwork::getInstance(engine).connect(host, udpPort, false);
        }
    }

    static bool firstTime = false;

    void updateClientNetworkTCP(bool playButton)
    {
        ClientNetwork &clientNetwork = ClientNetwork::getInstance();

        if (playButton && !firstTime) {
            clientNetwork.send201();
            firstTime = true;
        }

        if (clientNetwork.isConnectedUDP && !isCoUDP) {
            isCoUDP = true;
        }

        clientNetwork.startAsyncReceiveTCP(clientNetwork.getTCPSocket());
        clientNetwork.handleNetwork();
    }

    void setEngineToNetwork(GameEngine::GameEngine &engine)
    {
        ClientNetwork::getInstance().setEngine(engine);
    }

    void updateClientNetworkUDP()
    {
        GameEngine::Events::Type type;
        ClientNetwork &clientNetwork = ClientNetwork::getInstance();

        clientNetwork.asyncReceive(clientNetwork.getUDPSocket());
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
