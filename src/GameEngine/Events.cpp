/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Events
*/

#include "GameEngine/Events.hpp"

namespace GameEngine {

    std::queue<Events::Type> Events::mQueue = std::queue<Events::Type>();

    void Events::push(Type event)
    {
        Events::mQueue.push(event);
    }

    bool Events::poll(Type &event)
    {
        if (Events::mQueue.empty()) { return false; }
        event = Events::mQueue.front();
        Events::mQueue.pop();
        return true;
    }
}
