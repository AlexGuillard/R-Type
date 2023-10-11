/*
** EPITECH PROJECT, 2023
** sendCode
** File description:
** sendCode
*/

#pragma once
#include <iostream>
#include "INetwork.hpp"

namespace Network::Send {
    std::string makeHeader(int code, int entityNb);
    std::string makeBodyMob(int xMob, int yMob, Enums::Position pos);
    std::string makeBodyAlly(int xAlly, int yAlly, Enums::PlayerColor actualColor);
    std::string makeBodyMissile(const int pos[2], const int velocity[2], Enums::TeamGroup team, int strenght);

    std::string makeBinaryInt(int number);

    std::string codeMob(int code, int ide, int xMob, int yMob, Enums::Position pos);

    std::string codeAlly(int code, int ide, int xMob, int yMob, Enums::PlayerColor color);

    std::string codeMissil(const int header[2], const int pos[2], const int velocity[2], Enums::TeamGroup team, int strenght);
};
