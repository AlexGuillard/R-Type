/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** AssetLoader
*/

#pragma once

#include <string>
#include <raylib.h>
#include <unordered_map>

#include "assets/generatedAssets.hpp"

namespace Assets {
    class AssetLoader {
    public:
        /**
         * @brief Loads an image from the one embeded in the executable.
         * Images loaded from this function are cached.
         * @param index index of the image
         * @param extension The extension of the file (ex: '.png', '.gif')
         * @returns A raylib image
        */
        static Image loadImage(AssetsIndex index, const std::string &extension);
        /**
         * @brief Loads a Png image from the one embeded in the executable.
         * Images loaded from this function are cached.
         * @param index index of the image
         * @returns A raylib image
        */
        static Image loadImagePng(AssetsIndex index);
        /**
         * @brief Loads a Gif image from the one embeded in the executable
         * Images loaded from this function are cached.
         * @param index index of the image
         * @returns A raylib image
        */
        static Image loadImageGif(AssetsIndex index);
        /**
         * @brief Loads an image from the one embeded in the executable.
         * Images loaded from this function are cached.
         * @param index index of the image
         * @param extension The extension of the file (ex: '.png', '.gif')
         * @returns A raylib image
        */
        static Texture2D loadTexture(AssetsIndex index, const std::string &extension);
        /**
         * @brief Loads a Png texture from the one embeded in the executable.
         * Images loaded from this function are cached.
         * @param index index of the texture
         * @returns A raylib texture
        */
        static Texture2D loadTexturePng(AssetsIndex index);
        /**
         * @brief Loads a Gif texture from the one embeded in the executable
         * Images loaded from this function are cached.
         * @param index index of the texture
         * @returns A raylib texture
        */
        static Texture2D loadTextureGif(AssetsIndex index);
        /**
         * @brief Clears the cache of images
        */
        static void clearImageCache();
        /**
         * @brief Clears the cache of textures
        */
        static void clearTextureCache();
        /**
         * @brief Clears the cache of images and textures
        */
        static void clearCache();

    private:
        static std::unordered_map<AssetsIndex, Image> imageCache;
        static std::unordered_map<AssetsIndex, Texture2D> textureCache;
    };
}
