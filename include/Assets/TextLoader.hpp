/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** AssetLoader
*/

#pragma once

#include <string>

#include "Assets/generatedAssets.hpp"

namespace Assets {
    class TextLoader {
    public:
        /**
         * @brief Loads a text from the one embeded in the executable
         *
         * @param index index of the text
         * @return std::string
         */
        static std::string loadText(AssetsIndex index);
    };
}
