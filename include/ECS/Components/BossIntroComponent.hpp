/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** BossIntroComponent
*/

#pragma once

namespace ECS::Components {
    /**
     * @brief Component for the boss intro
     * @param length The length of the intro
     * @param _startX The starting x position of the boss (internal)
     * @param _time The time left before the intro ends (internal)
     * @param _isIntro Is the boss intro still playing (internal)
     */
    struct BossIntroComponent {
        double length = 5.0;
        float _startX = 0.0F;
        double _timer = -1;
        bool _isIntro = true;
    };

} // namespace ECS::Components
