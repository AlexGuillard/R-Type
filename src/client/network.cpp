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

    bool startClientNetwork(const std::string &host, int port, Network::ConnectionType type, Enums::MultiState multi, Enums::ModeSelect mode, GameEngine::GameEngine &engine)
    {
        //TODO:
        //connect return a bool to let us know if the connection was successful or not
        if (type == Network::ConnectionType::TCP) {
            std::cout << "Connecting TCP " << host << ":" << port << std::endl;
            return ClientNetwork::getInstance(engine).connect(host, port, true, multi);
        } else {
            std::cout << "Connecting UDP " << host << ":" << port << std::endl;
            return ClientNetwork::getInstance(engine).connect(host, port, false, multi);
        }
    }

    static bool firstTime = false;

    void updateClientNetworkTCP(bool playButton, Enums::ModeSelect mode)
    {
        static bool asyncReceiveStarted = false;
        ClientNetwork &clientNetwork = ClientNetwork::getInstance();

        if (!asyncReceiveStarted) {
            clientNetwork.startAsyncReceiveTCP(clientNetwork.getTCPSocket());
            asyncReceiveStarted = true;
        }
        if (playButton && !firstTime) {
            clientNetwork.send201(mode);
            firstTime = true;
        }

        if (clientNetwork.isConnectedUDP && !isCoUDP) {
            isCoUDP = true;
        }

        clientNetwork.handleNetwork();
    }

    void backMenu()
    {
        firstTime = false;
        isCoUDP = false;
        ClientNetwork::getInstance().isConnectedUDP = false;
        ClientNetwork::getInstance().resetEndGame();
        ClientNetwork::getInstance().send205();
    }

    void setEngineToNetwork(GameEngine::GameEngine &engine)
    {
        ClientNetwork::getInstance().setEngine(engine);
    }

    bool getWinningCondition()
    {
        return ClientNetwork::getInstance().getWinCondition();
    }

    bool getLeftWinningCondition()
    {
        return ClientNetwork::getInstance().getLeftWinCondition();
    }

    bool getRightWinningCondition()
    {
        return ClientNetwork::getInstance().getRightWinCondition();
    }

    bool getLoosingCondition()
    {
        return ClientNetwork::getInstance().getLooseCondition();
    }

    void updateClientNetworkUDP()
    {
        GameEngine::Events::Type type;
        ClientNetwork &clientNetwork = ClientNetwork::getInstance();

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

    bool check401Error()
    {
        return ClientNetwork::getInstance().getErrorServer();
    }
}
