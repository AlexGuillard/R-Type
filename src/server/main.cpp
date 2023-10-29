/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/

#include <csignal>
#include <iostream>
#include <thread>
#include <mutex>

#include "GameEngine/GameEngine.hpp"
#include "server/network/ServerNetwork.hpp"

bool isServerRunning = true;
boost::asio::io_service ioService;
std::mutex ioServiceMutex;

void signalHandler(int signum)
{
    std::lock_guard<std::mutex> lock(ioServiceMutex);
    isServerRunning = false;
    ioService.stop();
}

int main(int argc, char **argv)
{
    const int port = 4848;
    const int portUdp = 6084;
    const int error = 84;

    // catch CTRL-C
    signal(SIGINT, signalHandler);
    try {
        Network::ServerNetwork network(ioService, ioServiceMutex, port, portUdp);
        while (isServerRunning) {
            network.update();
        }
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return error;
    }
    std::cout << "Server closed" << std::endl;
    return (0);
}
