/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Events
*/

#pragma once

#include <queue>

namespace GameEngine {
    class Events {
    public:
        enum class Type {
            NONE = 0,
            PLAYER_UP,
            PLAYER_DOWN,
            PLAYER_LEFT,
            PLAYER_RIGHT,
            PLAYER_SHOOT,
            PLAYER_FORCE,
            PLAYER_DROP = PLAYER_FORCE,
            COUNT
        };

        /**
         * @brief Push a new event to the queue
        */
        static void push(Type event);
        /**
         * @brief Pop the event on top of the event queue, if any, and return it.
         *
         * This function is not blocking: if there's no pending event then it
         * will return false and leave event unmodified.
         * Note that more than one event may be present in the event queue,
         * thus you should always call this function in a loop to make sure
         * that you process every pending event.
         *
         * @returns True if an event was polled, false otherwise
        */
        static bool poll(Type &event);

    private:
        static std::queue<Type> mQueue;
        Events() = default;
        ~Events() = default;
        Events(const Events &) = delete;
    };

}
