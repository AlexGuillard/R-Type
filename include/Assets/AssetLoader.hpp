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

#include "Assets/generatedAssets.hpp"

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
         * @brief Loads a Jpg image from the one embeded in the executable.
         * Images loaded from this function are cached.
         * @param index index of the image
         * @returns A raylib image
        */
        static Image loadImageJpg(AssetsIndex index);
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
         * @brief Loads a Jpg texture from the one embeded in the executable.
         * Images loaded from this function are cached.
         * @param index index of the texture
         * @returns A raylib texture
        */
        static Texture2D loadTextureJpg(AssetsIndex index);
        /**
         * @brief Loads a Gif texture from the one embeded in the executable
         * Images loaded from this function are cached.
         * @param index index of the texture
         * @returns A raylib texture
        */
        static Texture2D loadTextureGif(AssetsIndex index);
         /**
         * @brief Loads an music from the one embeded in the executable.
         * Music loaded from this function are cached.
         * @param index index of the music
         * @param extension The extension of the file (ex: '.wav', 'mp3')
         * @param loop indicates if the music should loop
         * @returns A raylib music
        */
        static Music loadMusic(AssetsIndex index, const std::string &extension, bool loop);
        /**
         * @brief Loads an sound from the one embeded in the executable.
         * Sounds loaded from this function are cached.
         * @param index index of the sound
         * @param extension The extension of the file (ex: '.wav', '.mp3', '.ogg')
         * @returns A raylib sound
        */
        static Sound loadSound(AssetsIndex index, const std::string &extension);
        /**
         * @brief Loads a wav sound from the one embeded in the executable.
         * Sounds loaded from this function are cached.
         * @param index index of the sound
         * @returns A raylib sound
        */
        static Sound loadSoundWav(AssetsIndex index);
        /**
         * @brief Loads a ogg sound from the one embeded in the executable.
         * Sounds loaded from this function are cached.
         * @param index index of the sound
         * @returns A raylib sound
        */
        static Sound loadSoundOgg(AssetsIndex index);
        /**
         * @brief Loads a mp3 sound from the one embeded in the executable.
         * Sounds loaded from this function are cached.
         * @param index index of the sound
         * @returns A raylib sound
        */
        static Sound loadSoundMp3(AssetsIndex index);
        /**
         * @brief Clears the cache of images
        */
        static void clearImageCache();
        /**
         * @brief Clears the cache of textures
        */
        static void clearTextureCache();
        /**
        * @brief Clears the cache of music
        */
        static void clearMusicCache();
        /**
        * @brief Clears the cache of sound
        */
        static void clearSoundCache();
        /**
         * @brief Clears the cache of images, textures, musics and sounds
        */
        static void clearCache();

    private:
        // Cache of Images. Used to avoid having to reload the same image thousands of time
        static std::unordered_map<AssetsIndex, Image> imageCache;
        // Cache of Textures. Used to avoid having to reload the same image thousands of time
        static std::unordered_map<AssetsIndex, Texture2D> textureCache;
        // Cache of Musics. Used to avoid having to reload the same music thousands of time
        static std::unordered_map<AssetsIndex, Music> musicCache;
        // Cache of Sounds. Used to avoid having to reload the same sound thousands of time
        static std::unordered_map<AssetsIndex, Sound> soundCache;
    };
}
