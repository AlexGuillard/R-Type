/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/

#include <iostream>
#include "client/display/Display.hpp"

// int main() {
//     boost::asio::io_service io_service;
//     std::string host = "192.168.122.1";
//     int port = 4848;
//     Network::ClientNetwork client(io_service, host, port);
//     client.start();
// 	client.sendAction(Network::Action::SHOOT);
// 	client.sendAction(Network::Action::DROP);
//     io_service.run();
//     return 0;
// }

int main()
{
	Screen::Display window;
	window.displayWindow();
}

