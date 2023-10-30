/*
** EPITECH PROJECT, 2023
** recupInfo
** File description:
** recupInfo
*/

#include "server/network/recupInfo.hpp"
#include "Assets/TextLoader.hpp"

std::vector<Network::Info> Network::RecupInfo::getScript() {
    return _data;
}

std::vector<Network::Info> Network::RecupInfo::getTickScript(std::size_t tick) {
    std::vector<Network::Info> data;
    for (int i = 0; i != _data.size(); i++) {
        if (_data[i].tick == tick) {
            data.push_back(_data[i]);
        }
    }
    return data;
}

void Network::RecupInfo::openFile(Assets::AssetsIndex script) {
    _data.clear();
    std::string fill = Assets::TextLoader::loadText(script);
    std::istringstream ss(fill);
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(ss, line, '\n')) {
        lines.push_back(line);
    }
    for (int i = 0; i < lines.size(); i++) {
        Network::Info data;
        std::istringstream ss(lines[i]);
        std::string element;
        std::vector<std::string> elements;
        while (std::getline(ss, element, ' ')) {
            elements.push_back(element);
        }
        data.rfc = std::stoull(elements[0]);
        data.y = std::stoull(elements[1]);
        data.tick = std::stoull(elements[2]);
        if (element.size() > 3) {
            if (elements[3] == "down"){
                data.extraType = Network::Info::SIDE;
                data.extra.side = Enums::Position::DOWN;
            } else if (elements[3] == "up") {
                data.extraType = Network::Info::SIDE;
                data.extra.side = Enums::Position::UP;
            }
        } else {
            data.extra.side = Enums::Position::NONE;
            data.extraType = Network::Info::NONE;
        }
        _data.push_back(data);
    }
}

void Network::RecupInfo::openLVL(int level) {
    if (level == 1) {
        openFile(Assets::AssetsIndex::SCRIPT_STAGE_1_TXT);
        return;
    }
    if (level == 2) {
        openFile(Assets::AssetsIndex::SCRIPT_STAGE_2_TXT);
        return;
    }
    openFile(Assets::AssetsIndex::SCRIPT_STAGE_1_TXT);
}

Network::RecupInfo::RecupInfo() {
}

Network::RecupInfo::~RecupInfo() {
}
