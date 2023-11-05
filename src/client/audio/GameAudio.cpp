/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Sound.cpp
*/
#include <iostream>
#include "client/audio/GameAudio.hpp"
#include "Assets/AssetLoader.hpp"

void GameAudio::playSound(Assets::AssetsIndex index, const std::string &extension)
{
    PlaySound(Assets::AssetLoader::loadSound(index, extension));
}

void GameAudio::playMusic(Assets::AssetsIndex index, const std::string &extension, bool loop, double volume)
{
    PlayMusicStream(Assets::AssetLoader::loadMusic(index, extension, loop));
    _musicPlaying = true;
    _musicIndex = index;
    _musicExtension = extension;
    _musicLoop = loop;
    setVolumeMusic(volume);
}
void GameAudio::updateMusicStream()
{
    if (!_musicPlaying)
        return;
    UpdateMusicStream(Assets::AssetLoader::loadMusic(_musicIndex, _musicExtension, _musicLoop));
}

void GameAudio::stopMusic()
{
    StopMusicStream(Assets::AssetLoader::loadMusic(_musicIndex, _musicExtension, _musicLoop));
    _musicPlaying = false;
}

void GameAudio::changeMusic(Assets::AssetsIndex index, const std::string &extension,
bool loop, double volume)
{
    if (index != _musicIndex) {
        if (_musicPlaying)  {
            stopMusic();
            UnloadMusicStream(Assets::AssetLoader::loadMusic(_musicIndex, _musicExtension, _musicLoop));
        }
        playMusic(index, extension, loop, volume);
    }
}

void GameAudio::setVolumeMusic(double volume)
{
    if (volume < 0.0 || volume > 1.0)
        return;
    if (_musicPlaying) {
        SetMusicVolume(Assets::AssetLoader::loadMusic(_musicIndex, _musicExtension, _musicLoop), volume);
    }
}

GameAudio::~GameAudio()
{
    if (_musicPlaying) {
        UnloadMusicStream(Assets::AssetLoader::loadMusic(_musicIndex, _musicExtension, _musicLoop));
    }
}
