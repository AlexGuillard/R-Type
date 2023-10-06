

#include <iostream>

#include <raylib.h>

#include "Assets/AssetLoader.hpp"

namespace Assets {
    std::unordered_map<AssetsIndex, Image> AssetLoader::imageCache;
    std::unordered_map<AssetsIndex, Texture2D> AssetLoader::textureCache;

    Image AssetLoader::loadImage(AssetsIndex index, const std::string &extension)
    {
        if (AssetLoader::imageCache.contains(index)) {
            return AssetLoader::imageCache[index];
        }
        Assets::assets[static_cast<uint16_t>(index)];
        auto &&[data, dataSize] = Assets::assets[static_cast<uint16_t>(index)];
        AssetLoader::imageCache[index] = LoadImageFromMemory(extension.c_str(), *data, dataSize);
        return AssetLoader::imageCache[index];
    }

    Image AssetLoader::loadImagePng(AssetsIndex index)
    {
        return AssetLoader::loadImage(index, ".png");
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

    Texture2D AssetLoader::loadTextureGif(AssetsIndex index)
    {
        return AssetLoader::loadTexture(index, ".gif");
    }

    void AssetLoader::clearImageCache()
    {
        AssetLoader::imageCache.clear();
    }

    void AssetLoader::clearTextureCache()
    {
        AssetLoader::textureCache.clear();
    }

    void AssetLoader::clearCache()
    {
        AssetLoader::clearImageCache();
        AssetLoader::clearTextureCache();
    }
}
