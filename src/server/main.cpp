/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/
#include <asio.hpp>
#include "server/network/ServerNetwork.hpp"

int main(int argc, char **argv)
{
    boost::asio::io_service ioService;
    Network::ServerNetwork network(ioService, 4242);
    ioService.run();
    return (0);
}
