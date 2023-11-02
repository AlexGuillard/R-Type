/*
** EPITECH PROJECT, 2023
** sendCode.cpp
** File description:
** sendCode
*/

#include "server/network/sendCode.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"

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
    std::memcpy(str.data(), &res, sizeof(Network::BodyNumber));
    return str;
}

std::string Network::Send::makeBodyPosition(ECS::Components::PositionComponent pos)
{
    std::string str;

    str.resize(sizeof(ECS::Components::PositionComponent));
    std::memcpy(str.data(), &pos, sizeof(ECS::Components::PositionComponent));
    return str;
}

std::string Network::Send::makeBodyVelocity(ECS::Components::VelocityComponent vel)
{
    std::string str;

    str.resize(sizeof(ECS::Components::VelocityComponent));
    std::memcpy(str.data(), &vel, sizeof(ECS::Components::VelocityComponent));
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

std::string Network::Send::makeBodyAlly(int xAlly, int yAlly, Enums::PlayerColor actualColor, Enums::TeamGroup team)
{
    Network::bodyAlly res;
    std::string str;

    str.resize(sizeof(Network::bodyAlly));
    res.x = xAlly;
    res.y = yAlly;
    res.color = actualColor;
    res.team = team;
    std::memcpy(&str.data()[0], &res, sizeof(Network::bodyAlly));
    return str;
}

std::string Network::Send::makeBodyMissile(const std::array<float, 2> &posXY, const std::array<float, 2> &velocityXY, Enums::TeamGroup team, int strenght)
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

std::string Network::Send::codeMissile(const std::array<int, 2> &header, const std::array<float, 2> &pos, const std::array<float, 2> &velocity, Enums::TeamGroup team, int strenght)
{
    std::string str;

    str = makeHeader(header[0], header[1]);
    str.append(makeBodyMissile(pos, velocity, team, strenght));
    str.append(makeBodyNum(header[0]));
    return str;
}

Network::BodyNumber Network::Send::stringToBodyNum(std::string &code)
{
    BodyNumber res;

    std::memcpy(&res, code.data(), sizeof(BodyNumber));
    code.erase(0, sizeof(BodyNumber));
    return res;
}

Network::header Network::Send::stringToheader(std::string code)
{
    header res;

    std::memcpy(&res, code.data(), sizeof(header));
    code.erase(0, sizeof(header));
    return res;
}
