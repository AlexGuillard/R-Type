/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Events
*/

#include "GameEngine/Events.hpp"

namespace GameEngine {

    std::vector<Events::Type> Events::mQueue = std::vector<Events::Type>();
    std::vector<int> Events::mQueueId = std::vector<int>();

    void Events::push(Type event)
    {
        Events::push(event, -1);
    }

    bool Events::poll(Type &event)
    {
        int idx = -1;

        return Events::poll(event, idx);
    }

    void Events::push(Type event, int idx)
    {
        Events::mQueue.insert(Events::mQueue.begin(), event);
        Events::mQueueId.insert(Events::mQueueId.begin(), idx);
    }

    bool Events::poll(Type &event, int &idx)
    {
        if (Events::mQueue.empty()) { return false; }
        event = Events::mQueue.back();
        idx = Events::mQueueId.back();
        Events::mQueue.pop_back();
        Events::mQueueId.pop_back();
        return true;
    }

    std::vector<Events::Type>::iterator Events::begin()
    {
        return Events::mQueue.begin();
    }

    std::vector<Events::Type>::iterator Events::end()
    {
        return Events::mQueue.end();
    }
}
