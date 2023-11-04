/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Sound.cpp
*/

#include "client/audio/GameSound.hpp"
#include "Assets/AssetLoader.hpp"

void GameSound::playSound(Assets::AssetsIndex index, const std::string &extension)
{
    PlaySound(Assets::AssetLoader::loadSound(index, extension));
}

void GameSound::playMusic(Assets::AssetsIndex index, const std::string &extension)
{
    PlayMusicStream(Assets::AssetLoader::loadMusic(index, extension));
    _musicPlaying = true;
    _musicIndex = index;
    _musicExtension = extension;
}
void GameSound::updateMusicStream()
{
    if (!_musicPlaying)
        return;
    UpdateMusicStream(Assets::AssetLoader::loadMusic(_musicIndex, _musicExtension));
}

void GameSound::stopMusic()
{
    StopMusicStream(Assets::AssetLoader::loadMusic(_musicIndex, _musicExtension));
    _musicPlaying = false;
}

void GameSound::setVolume(double volume)
{
    if (volume < 0.0 || volume > 1.0)
        return;
    if (_musicPlaying) {
        SetMusicVolume(Assets::AssetLoader::loadMusic(_musicIndex, _musicExtension), volume);
    }
}
