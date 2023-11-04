/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Sound.hpp
*/

#include <raylib.h>
#include "Assets/generatedAssets.hpp"

class GameSound {
    /**
     * @brief Sound class, to use a raylib sound
    */
    public:
        /**
          * @brief create a GameSound
        **/
        GameSound(Assets::AssetsIndex index = Assets::AssetsIndex::SPACESHIP_SHOTTING_WAV, const std::string &extension = ".wav", double volume = 1.0);
        /**
         * @brief destroy the GameSound object and unload Sound
        **/
        ~GameSound();
        /**
         * @brief get sound variable
        **/
        Sound &getSound();
        /**
         * @brief set sound variable
         * @param sound raylib sound
        **/
        void setSound(Sound sound);
        /**
         * @brief init sound variable
         * @param index index of the sound in the assets
         * @param extension extension of the sound
         * supported extension type: ".wav", ".mp3", ".ogg"
        **/
        void initSound(Assets::AssetsIndex index, const std::string &extension);
        /**
         * @brief play raylib sound
        **/
        void playSound();
        /**
         * @brief set volume of the sound
         * @param volume volume of the sound
         * volume must be between 0.0 and 1.0
        **/
        void setVolume(double volume);

    private:
        Sound sound;
};
