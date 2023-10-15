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
    /**
     * @brief function to create a header struct in std::string
     *
     * @param code rfc code
     * @param entityNb number for color of client
     * @return std::string
     */
    std::string makeHeader(int code, int entityNb);
    /**
     * @brief function to create a header BodyNumber in std::string
     *
     * @param num number
     * @return std::string
     */
    std::string makeBodyNum(int num);
    /**
     * @brief function to create a BodyMob struct in std::string
     *
     * @param xMob position x of mob
     * @param yMob position y of mob
     * @param pos enum if up or down
     * @return std::string
     */
    std::string makeBodyMob(int xMob, int yMob, Enums::Position pos);
    /**
     * @brief function to create a BodyAlly struct in std::string
     *
     * @param xAlly position x of Ally
     * @param yAlly position y of Ally
     * @param actualColor enum of color of ally
     * @return std::string
     */
    std::string makeBodyAlly(int xAlly, int yAlly, Enums::PlayerColor actualColor);
    /**
     * @brief function to create a BodyMissile struct in std::string
     *
     * @param pos position x and y of Missile
     * @param velocity velocity x and y of Missile
     * @param team enum for Ally or ennemy team missile
     * @param strenght power of the missile (-1 if not set)
     * @return std::string
     */
    std::string makeBodyMissile(const int pos[2], const int velocity[2], Enums::TeamGroup team, int strenght);
    /**
     * @brief called when spawn a mob
     *
     * @param code rfc code of mob (301 - 306)
     * @param ide number for entity to put in header
     * @param xMob position x of mob
     * @param yMob position y of mob
     * @param pos enum if up or down
     * @return std::string
     */
    std::string codeMob(int code, int ide, int xMob, int yMob, Enums::Position pos);
    /**
     * @brief called when spawn a ally
     *
     * @param code rfc code of mob (311 - 312)
     * @param ide number for entity to put in header
     * @param xAlly position x of ally
     * @param yAlly position y of ally
     * @param color enum for color of the ally
     * @return std::string
     */
    std::string codeAlly(int code, int ide, int xAlly, int yAlly, Enums::PlayerColor color);
    /**
     * @brief called when spawn a missile
     *
     * @param header contain code rfc and entity for header struct
     * @param pos pos x and y of the missile
     * @param velocity pos x and y of the missile
     * @param team enum for type of team (ally, ennemy)
     * @param strenght power of the missile (-1 if not set)
     * @return std::string
     */
    std::string codeMissil(const int header[2], const int pos[2], const int velocity[2], Enums::TeamGroup team, int strenght);
    /**
     * @brief transform string send by client to int
     *
     * @param code string cotaining the rfc code
     * @return int
     */
    BodyNumber stringToBodyNum(std::string &code);
    Network::header stringToheader(std::string code);
};
