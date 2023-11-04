/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Music.cpp
*/

#include "client/audio/GameMusic.hpp"
#include "Assets/AssetLoader.hpp"
#include <iostream>

GameMusic::GameMusic(Assets::AssetsIndex index, const std::string &extension, double volume)
{
    initMusic(index, extension);
    this->setVolume(volume);
    this->setIsPlaying(true);
}

GameMusic::~GameMusic()
{
    UnloadMusicStream(this->getMusic());
}

Music &GameMusic::getMusic()
{
    return this->music;
}

bool GameMusic::getIsPlaying()
{
    return this->isPlaying;
}

void GameMusic::setIsPlaying(bool isPlaying)
{
    this->isPlaying = isPlaying;
}

void GameMusic::setMusic(Music music)
{
    this->music = music;
}

void GameMusic::initMusic(Assets::AssetsIndex index, const std::string &extension)
{
    if (extension == ".wav") {
        this->setMusic(Assets::AssetLoader::loadMusicWav(index));
    } else if (extension == ".ogg") {
        this->setMusic(Assets::AssetLoader::loadMusicOgg(index));
    } else if (extension == ".mp3") {
        this->setMusic(Assets::AssetLoader::loadMusicMp3(index));
    }
}

void GameMusic::playMusic()
{
    PlayMusicStream(this->getMusic());
    this->setIsPlaying(true);
}

void GameMusic::setVolume(double volume)
{
    SetMusicVolume(this->getMusic(), volume);
}

void GameMusic::updateMusic()
{
    UpdateMusicStream(this->getMusic());
}

void GameMusic::pauseMusic()
{
    this->setIsPlaying(!this->getIsPlaying());

    if (this->getIsPlaying()) {
        PauseMusicStream(this->getMusic());
    } else {
        ResumeMusicStream(this->getMusic());
    }
}

void GameMusic::restartMusic()
{
    StopMusicStream(this->getMusic());
    PlayMusicStream(this->getMusic());
}