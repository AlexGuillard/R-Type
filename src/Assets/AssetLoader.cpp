

#include <iostream>

#include <raylib.h>

#include "Assets/AssetLoader.hpp"



namespace Assets {
    std::unordered_map<AssetsIndex, Image> AssetLoader::imageCache;
    std::unordered_map<AssetsIndex, Texture2D> AssetLoader::textureCache;
    std::unordered_map<AssetsIndex, Music> AssetLoader::musicCache;
    std::unordered_map<AssetsIndex, Sound> AssetLoader::soundCache;

    Image AssetLoader::loadImage(AssetsIndex index, const std::string &extension)
    {
        if (AssetLoader::imageCache.contains(index)) {
            return AssetLoader::imageCache[index];
        }
        auto &&[data, dataSize] = Assets::assets[static_cast<uint16_t>(index)];
        AssetLoader::imageCache[index] = LoadImageFromMemory(extension.c_str(), *data, dataSize);
        return AssetLoader::imageCache[index];
    }

    Image AssetLoader::loadImagePng(AssetsIndex index)
    {
        return AssetLoader::loadImage(index, ".png");
    }

    Image AssetLoader::loadImageJpg(AssetsIndex index)
    {
        return AssetLoader::loadImage(index, ".jpg");
    }

    Image AssetLoader::loadImageGif(AssetsIndex index)
    {
        return AssetLoader::loadImage(index, ".gif");
    }

    Texture2D AssetLoader::loadTexture(AssetsIndex index, const std::string &extension)
    {
        if (!AssetLoader::textureCache.contains(index)) {
            Image image = AssetLoader::loadImage(index, extension);
            AssetLoader::textureCache[index] = LoadTextureFromImage(image);
        }
        return AssetLoader::textureCache[index];
    }

    Texture2D AssetLoader::loadTexturePng(AssetsIndex index)
    {
        return AssetLoader::loadTexture(index, ".png");
    }

    Texture2D AssetLoader::loadTextureJpg(AssetsIndex index)
    {
        return AssetLoader::loadTexture(index, ".jpg");
    }

    Texture2D AssetLoader::loadTextureGif(AssetsIndex index)
    {
        return AssetLoader::loadTexture(index, ".gif");
    }

    Music AssetLoader::loadMusic(AssetsIndex index, const std::string &extension, bool loop)
    {
        if (AssetLoader::musicCache.contains(index)) {
            return AssetLoader::musicCache[index];
        }
        auto &&[data, dataSize] = Assets::assets[static_cast<uint16_t>(index)];
        AssetLoader::musicCache[index] = LoadMusicStreamFromMemory(extension.c_str(),*data, dataSize);
        AssetLoader::musicCache[index].looping = loop;
        return AssetLoader::musicCache[index];
    }

    Sound AssetLoader::loadSound(AssetsIndex index, const std::string &extension)
    {
        if (AssetLoader::soundCache.contains(index)) {
            return AssetLoader::soundCache[index];
        }
        auto &&[data, dataSize] = Assets::assets[static_cast<uint16_t>(index)];
        Wave wave = LoadWaveFromMemory(extension.c_str(),*data, dataSize);
        AssetLoader::soundCache[index] = LoadSoundFromWave(wave);
        return AssetLoader::soundCache[index];
    }

    Sound AssetLoader::loadSoundWav(AssetsIndex index)
    {
        return AssetLoader::loadSound(index, ".wav");
    }

    Sound AssetLoader::loadSoundOgg(AssetsIndex index)
    {
        return AssetLoader::loadSound(index, ".ogg");
    }

    Sound AssetLoader::loadSoundMp3(AssetsIndex index)
    {
        return AssetLoader::loadSound(index, ".mp3");
    }

    void AssetLoader::clearImageCache()
    {
        AssetLoader::imageCache.clear();
    }

    void AssetLoader::clearTextureCache()
    {
        AssetLoader::textureCache.clear();
    }

    void AssetLoader::clearMusicCache()
    {
        for (auto &&[index, music] : AssetLoader::musicCache) {
            UnloadMusicStream(music);
        }
        AssetLoader::musicCache.clear();
    }

    void AssetLoader::clearSoundCache()
    {
        for (auto &&[index, sound] : AssetLoader::soundCache) {
            UnloadSound(sound);
        }
        AssetLoader::soundCache.clear();
    }

    void AssetLoader::clearCache()
    {
        AssetLoader::clearImageCache();
        AssetLoader::clearTextureCache();
        AssetLoader::clearMusicCache();
        AssetLoader::clearSoundCache();
    }
}
