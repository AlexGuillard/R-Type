/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/

#include <csignal>

#include "GameEngine/GameEngine.hpp"
#include "server/network/ServerNetwork.hpp"

static bool isServerRunning = true;

int main(int argc, char **argv)
{
    const int port = 4848;
    const int portUdp = 6084;
    const int error = 84;
    GameEngine::GameEngine engine = GameEngine::createServerEngine();

    // catch CTRL-C
    signal(SIGINT, [](int) {
        isServerRunning = false;
        }
    );
    try {
        boost::asio::io_service ioService;
        Network::ServerNetwork network(ioService, port, portUdp);
        while (isServerRunning) {
            network.run(engine);
        }
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return error;
    }
    std::cout << "Server closed" << std::endl;
    return (0);
}
