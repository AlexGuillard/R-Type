/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/
#include <boost/asio.hpp>
#include "server/network/ServerNetwork.hpp"

int main(int argc, char **argv)
{
    const int port = 4848;
    boost::asio::io_service ioService;
    Network::ServerNetwork network(ioService, port);
    ioService.run();
    return (0);
}
