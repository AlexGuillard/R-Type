/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/

#include "GameEngine/GameEngine.hpp"
#include "server/network/ServerNetwork.hpp"

int main(int argc, char **argv)
{
    const int port = 4848;
    const int portUdp = 6084;
    const int error = 84;
    GameEngine::GameEngine engine = GameEngine::createServerEngine();

    try {
        boost::asio::io_service ioService;
        Network::ServerNetwork network(ioService, port, portUdp);
        while (true) {
            if (!network.isGameRunning()) {
                network.tcpConnection();
            } else {
                network.udpConnection();
            }
            network.run(engine);
        }
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return error;
    }
    return (0);
}
