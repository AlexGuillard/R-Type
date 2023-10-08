/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/
#include "server/network/ServerNetwork.hpp"

int main(int argc, char **argv)
{
    const int port = 4848;
    const int error = 84;

    try {
        boost::asio::io_service ioService;
        Network::ServerNetwork network(ioService, port);
    } catch(const std::exception &e) {
        std::cout << e.what() << std::endl;
        return error;
    }
    return (0);
}
