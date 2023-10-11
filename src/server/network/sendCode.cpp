/*
** EPITECH PROJECT, 2023
** sendCode.cpp
** File description:
** sendCode
*/

#include "sendCode.hpp"

std::string Network::Send::makeHeader(int code, int entityNb)
{
    Network::header res;
    std::string str;

    str.resize(sizeof(Network::header));
    res.codeRfc = code;
    res.entity = entityNb;
    std::memcpy(str.data(), &res, sizeof(Network::header));
    return str;
}

std::string Network::Send::makeBodyMob(int xMob, int yMob)
{
    Network::bodyMob res;
    std::string str;

    str.resize(sizeof(Network::bodyMob));
    res.x = xMob;
    res.y = yMob;
    std::memcpy(str.data(), &res, sizeof(Network::bodyMob));
    return str;
}

std::string Network::Send::makeBodyAlly(int xAlly, int yAlly, Enums::PlayerColor actualColor)
{
    Network::bodyAlly res;
    std::string str;

    str.resize(sizeof(Network::bodyAlly));
    res.x = xAlly;
    res.y = yAlly;
    res.color = actualColor;
    std::memcpy(str.data(), &res, sizeof(Network::bodyAlly));
    return str;
}

std::string Network::Send::makeBodyMissile(const int posXY[2], const int velocityXY[2], Enums::TeamGroup team, int strenght)
{
    Network::bodyMissile res;
    std::string str;

    str.resize(sizeof(Network::bodyMissile));
    res.x = posXY[0];
    res.y = posXY[1];
    res.velocityX = velocityXY[0];
    res.velocityY = velocityXY[1];
    res.team = team;
    res.strength = strenght;
    std::memcpy(str.data(), &res, sizeof(Network::bodyMissile));
    return str;
}

std::string Network::Send::makeBinaryInt(int number)
{
    std::string str;

    str.resize(sizeof(int));
    std::memcpy(str.data(), &number, sizeof(int));
    return str;
}

std::string Network::Send::code301(int ide, int xPata, int yPata)
{
    std::string str;

    str = makeHeader(301, ide);
    str.append(makeBodyMob(xPata, yPata));
    str.append(makeBinaryInt(301));
    return str;
}
