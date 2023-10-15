/*
** EPITECH PROJECT, 2023
** sendCode.cpp
** File description:
** sendCode
*/

#include "server/network/sendCode.hpp"

std::string Network::Send::makeHeader(int code, int entityNb)
{
    Network::header res;
    std::string str;

    str.resize(sizeof(Network::header));
    res.codeRfc = code;
    res.entity = entityNb;
    std::memcpy(&str.data()[0], &res, sizeof(Network::header));
    return str;
}

std::string Network::Send::makeBodyNum(int num)
{
    Network::BodyNumber res;
    std::string str;

    str.resize(sizeof(Network::BodyNumber));
    res.number = num;
    // res.garbage = 20;
    std::memcpy(str.data(), &res, sizeof(Network::BodyNumber));
    return str;
}

std::string Network::Send::makeBodyMob(int xMob, int yMob, Enums::Position pos)
{
    Network::bodyMob res;
    std::string str;

    str.resize(sizeof(Network::bodyMob));
    res.x = xMob;
    res.y = yMob;
    res.pos = pos;
    std::memcpy(&str.data()[0], &res, sizeof(Network::bodyMob));
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
    std::memcpy(&str.data()[0], &res, sizeof(Network::bodyAlly));
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
    std::memcpy(&str.data()[0], &res, sizeof(Network::bodyMissile));
    return str;
}

std::string Network::Send::codeMob(int code, int ide, int xPata, int yPata, Enums::Position pos)
{
    std::string str;

    str = makeHeader(code, ide);
    str.append(makeBodyMob(xPata, yPata, pos));
    str.append(makeBodyNum(code));
    return str;
}

std::string Network::Send::codeAlly(int code, int ide, int xMob, int yMob, Enums::PlayerColor color)
{
    std::string str;

    str = makeHeader(code, ide);
    str.append(makeBodyAlly(xMob, yMob, color));
    str.append(makeBodyNum(code));
    return str;
}

std::string Network::Send::codeMissil(const int header[2], const int pos[2], const int velocity[2], Enums::TeamGroup team, int strenght)
{
    std::string str;

    str = makeHeader(header[0], header[1]);
    str.append(makeBodyMissile(pos, velocity, team, strenght));
    str.append(makeBodyNum(header[0]));
    return str;
}

Network::BodyNumber Network::Send::stringToBodyNum(std::string &code)
{
    BodyNumber res = { -1 };
    std::string copyCode(code.data());

    if (code.length() < sizeof(BodyNumber)) {
        return res;
    }
    std::memcpy(&res, copyCode.data(), sizeof(BodyNumber));
    code.erase(0, sizeof(BodyNumber));
    return res;
}
