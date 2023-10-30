/*
** EPITECH PROJECT, 2023
** IServerTcp.hpp
** File description:
** IServerTcp
*/

#pragma once
#include <iostream>
#include <boost/asio.hpp>

namespace Network {
    class IServerTcp {
        public:
            virtual ~IServerTcp() = default;
            virtual void start() = 0;
            virtual void waitRequest() = 0;
            virtual void write(std::string message) = 0;
            virtual void connection() = 0;
            virtual std::string codeLogin(int code, int entityId = -1) = 0;
            virtual void send202(int indexClient) = 0;
            virtual std::string code401() = 0;
            virtual void send201() = 0;
    };
}
