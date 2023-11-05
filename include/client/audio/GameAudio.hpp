/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Sound.hpp
*/

#include <raylib.h>
#include "Assets/generatedAssets.hpp"

class GameAudio {
    /**
     * @brief Sound class, to use a raylib sound
    */
    public:
        GameAudio() = default;
        ~GameAudio();
        void playSound(Assets::AssetsIndex index, const std::string &extension);
        void playMusic(Assets::AssetsIndex index, const std::string &extension,
        bool loop, double volume = 0.5);
        void updateMusicStream();
        void stopMusic();
        void changeMusic(Assets::AssetsIndex index, const std::string &extension,
        bool loop, double volume = 0.5);
        void setVolumeMusic(double volume);

    private:
        bool _musicPlaying = false;
        Assets::AssetsIndex _musicIndex;
        std::string _musicExtension;
        bool _musicLoop;
};
