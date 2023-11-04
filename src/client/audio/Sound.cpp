/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Sound.cpp
*/

#include "client/audio/Sound.hpp"
#include "Assets/AssetLoader.hpp"

GameSound::GameSound(Assets::AssetsIndex index, const std::string &extension, double volume)
{
    initSound(index, extension);
    this->setVolume(volume);
}

GameSound::~GameSound()
{
    UnloadSound(this->getSound());
}

Sound GameSound::getSound() const
{
    return this->sound;
}

void GameSound::setSound(Sound sound)
{
    this->sound = sound;
}

void GameSound::initSound(Assets::AssetsIndex index, const std::string &extension)
{
    if (extension == ".wav") {
        this->setSound(Assets::AssetLoader::loadSoundWav(index));
    } else if (extension == ".ogg") {
        this->setSound(Assets::AssetLoader::loadSoundOgg(index));
    } else if (extension == ".mp3") {
        this->setSound(Assets::AssetLoader::loadSoundMp3(index));
    }
}

void GameSound::playSound() const
{
    PlaySound(this->getSound());
}

void GameSound::setVolume(double volume) const
{
    SetSoundVolume(this->getSound(), volume);
}