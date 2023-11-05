/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Events
*/

#pragma once

#include <vector>

namespace GameEngine {
    class Events {
    public:
        enum class Type {
            NONE = 0,
            PLAYER_UP,
            PLAYER_DOWN,
            PLAYER_LEFT,
            PLAYER_RIGHT,
            PLAYER_SHOOT,                   // player is holding the shoot button
            PLAYER_FORCE,                   // player is holding the force button
            PLAYER_DROP = PLAYER_FORCE,
            PLAYER_MISSILE,                 // A player missile has been created
            PLAYER_WAVE_BEAM,               // A player wave beam has been created
            BYDO_SHOOT_MISSILE,             // Something wants to shoot a bydo shot
            BYDO_SHOOT_WAVE_BEAM,           // Something wants to shoot a bydo wave beam
            POD_SHOOT,                      // Pod wants to shoot something
            COUNT
        };

        /**
         * @brief Push a new event to the queue
        */
        static void push(Type event);
        /**
         * @brief Push a new event to the queue
         * @param event Event to push
         * @param idx Id of the player that triggered the event
         */
        static void push(Type event, int idx);
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
        /**
         * @brief Pop the event on top of the event queue, if any, and return it.
         *
         * @param event Variable to fill with the event
         * @param idx Variable to fill with the id of the player that triggered the event
         * @return True if an event was polled, false otherwise
         */
        static bool poll(Type &event, int &idx);

        static std::vector<Type>::iterator begin();
        static std::vector<Type>::iterator end();

    private:
        friend class Iterator;
        static std::vector<Type> mQueue;
        static std::vector<int> mQueueId;
        Events() = default;
        ~Events() = default;
        Events(const Events &) = delete;
    };

}
