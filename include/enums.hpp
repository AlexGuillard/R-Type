/*
** EPITECH PROJECT, 2023
** enums.hpp
** File description:
** enums
*/

#pragma once

namespace Enums {
    enum class PlayerColor {
        CYAN_COLOR,
        PURPLE_COLOR,
        LIME_COLOR,
        RED_COLOR,
        BLUE_COLOR,
        COUNT // keep last
    };

    enum class TeamGroup {
        NEUTRAL,
        ALLY,
        ENEMY
    };
    enum class Position {
        UP,
        DOWN
    };
    enum class RFCCode {
        CLIENT_CONNECT = 200,
        LAUNCH_GAME = 201,
        NEW_PLAYER = 202,
        PLAYER_UP = 211,
        PLAYER_DOWN = 212,
        PLAYER_LEFT = 213,
        PLAYER_RIGHT = 214,
        PLAYER_SHOOT = 215,
        PLAYER_DROP = 216,
    };
}
