/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Music.hpp
*/

#include <raylib.h>
#include "Assets/generatedAssets.hpp"

class GameMusic {
    /**
     * @brief Music class, to use a raylib music
    */
    public:
        /**
         * @brief create a GameMusic Object
        */
        GameMusic(Assets::AssetsIndex index = Assets::AssetsIndex::MAIN_MUSIC_WAV, const std::string &extension = ".wav", double volume = 1.0);
        /**
         * @brief destroy the Music object and unload Music
        */
        ~GameMusic();
        /**
         * @brief get music variable
        */
        Music &getMusic();
        /**
         * @brief get isPlaying variable, allows to know if music is playing
        */
        bool getIsPlaying();
        /**
         * @brief set isPlaying variable
         * @param isPlaying boolean
        */
        void setIsPlaying(bool isPlaying);
        /**
         * @brief set music variable
         * @param music raylib music
        */
        void setMusic(Music music);
        /**
         * @brief init music variable
         * @param index index of the music in the assets
         * @param extension extension of the music
         * supported extension type: ".wav", ".mp3", ".ogg"
        */
        void initMusic(Assets::AssetsIndex index, const std::string &extension);
        /**
         * @brief play raylib music
         **/
        void playMusic();
        /**
         * @brief set volume of the music
         * @param volume volume of the music
         * volume must be between 0.0 and 1.0
        **/
        void setVolume(double volume);
        /**
         * @brief update raylib music stream
        **/
        void updateMusic();
        /**
         * @brief pause raylib music
        **/
        void pauseMusic();
        /**
         * @brief resume raylib music
        **/
        void restartMusic();

    private:
        Music music;
        bool isPlaying;
};