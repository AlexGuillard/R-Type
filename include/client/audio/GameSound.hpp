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
        void playSound(Assets::AssetsIndex index, const std::string &extension);
        void playMusic(Assets::AssetsIndex index, const std::string &extension);
        void updateMusicStream();
        void stopMusic();
        /**
         * @brief set volume of the sound
         * @param volume volume of the sound
         * volume must be between 0.0 and 1.0
        **/
        void setVolume(double volume);

    private:
        bool _musicPlaying = false;
        Assets::AssetsIndex _musicIndex;
        std::string _musicExtension;
};
