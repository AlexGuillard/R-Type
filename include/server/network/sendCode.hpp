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
    std::string makeBodyMob(int xMob, int yMob);
    std::string makeBodyAlly(int xAlly, int yAlly, Enums::PlayerColor actualColor);
    std::string makeBodyMissile(const int pos[2], const int velocity[2], Enums::TeamGroup team, int strenght);

    std::string makeBinaryInt(int number);

    std::string code301(int ide, int xPata, int yPata);
    std::string code302(int ide, int xBink, int yBink);
    std::string code303(int ide, int xScant, int yScant);
    std::string code304(int ide, int xBug, int yBug);
    std::string code305(int ide, int xCancer, int yCancer);
    std::string code306(int ide, int xBlaster, int yBlaster);

    std::string code311();
    std::string code312();

    std::string code21();
    std::string code22();
    std::string code23();
};
