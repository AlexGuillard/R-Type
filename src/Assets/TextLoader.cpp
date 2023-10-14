/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** TextLoader
*/

#include "Assets/TextLoader.hpp"

namespace Assets {
    std::string TextLoader::loadText(AssetsIndex index)
    {
        auto &&[data, dataSize] = Assets::assets[static_cast<uint16_t>(index)];
        std::string result;
        for (uint16_t i = 0; i < dataSize; i++) {
            result += (*data)[i];
        }
        return result;
    }
}
