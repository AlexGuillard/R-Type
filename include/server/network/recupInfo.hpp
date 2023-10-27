/*
** EPITECH PROJECT, 2023
** recupInfo
** File description:
** recupInfo
*/

#ifndef RECUPINFO_HPP_
    #define RECUPINFO_HPP_

#include <cstddef>
#include <tuple>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "enums.hpp"
#include "Assets/TextLoader.hpp"

namespace Network {

    struct Info
    {
        std::size_t rfc;
        std::size_t y;
        std::size_t tick;
        enum ExtraType {
            SIDE,
            NONE,
        } extraType;
        union Extra
        {
            Enums::Position side;
        } extra;
    };


    class RecupInfo {
        public:
            /**
             * @brief Get the Script object
             *
             * @return std::vector<Info>
             */
            std::vector<Info> getScript();
            /**
             * @brief Get the Tick Script object
             *
             * @param tick
             * @return std::vector<Info>
             */
            std::vector<Info> getTickScript(std::size_t tick);
            /**
             * @brief
             *
             */
            void openFile(Assets::AssetsIndex script);
            /**
             * @brief Open script depend on level
             *
             */
            void openLVL(int level);
            /**
             * @brief Construct a new Recup Info object
             *
             */
            RecupInfo();
            /**
             * @brief Destroy the Recup Info object
             *
             */
            ~RecupInfo();
        protected:
            std::vector<Info> _data;
        private:
    };

};

#endif /* !RECUPINFO_HPP_ */
