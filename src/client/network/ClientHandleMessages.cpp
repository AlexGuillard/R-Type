/*
** EPITECH PROJECT, 2023
** ClientHandleMessages.cpp
** File description:
** ClientHandleMessages
*/

#include "client/network/ClientNetwork.hpp"
#include "server/network/sendCode.hpp"
#include "ECS/Creator.hpp"
#include "GameEngine/GameEngine.hpp"

//-----------------------------HANDLE MESSAGES--------------------------------------------//

void Network::ClientNetwork::initializeResponsehandler()
{
    // connection
    _responseHandlers[200] = [this](const header &h, std::string &s) {
        handleConnection(h, s);
        };
    _responseHandlers[201] = [this](const header &h, std::string &s) {
        handleLogin(h, s);
        };
    _responseHandlers[202] = [this](const header &h, std::string &s) {
        handleLogout(h, s);
        };

    // players
    _responseHandlers[311] = [this](const header &h, std::string &s) {
        handlePlayerSpawn(h, s);
        };
    _responseHandlers[312] = [this](const header &h, std::string &s) {
        handleAllySpawn(h, s);
        };

    // mobs
    _responseHandlers[301] = [this](const header &h, std::string &s) {
        handlePataPataSpawn(h, s);
        };
    _responseHandlers[302] = [this](const header &h, std::string &s) {
        handleBinkSpawn(h, s);
        };
    _responseHandlers[303] = [this](const header &h, std::string &s) {
        handleScantSpawn(h, s);
        };
    _responseHandlers[304] = [this](const header &h, std::string &s) {
        handleBugSpawn(h, s);
        };
    _responseHandlers[305] = [this](const header &h, std::string &s) {
        handleCancerSpawn(h, s);
        };
    _responseHandlers[306] = [this](const header &h, std::string &s) {
        handleBlasterSpawn(h, s);
        };
    // missiles
    _responseHandlers[321] = [this](const header &h, std::string &s) {
        handleClassicMissileSpawn(h, s);
        };
}

//-----------------------------MISSILES--------------------------------------------//

void Network::ClientNetwork::handleClassicMissileSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyMissile) + sizeof(BodyNumber)) {
        bodyMissile missileData = getMissile(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 321) {
            std::cout << "Entity: " << messageHeader.entity << " X: " << missileData.x << " Y: " << missileData.y << " VelocityX: " << missileData.velocityX << " VelocityY: " << missileData.velocityY << " Team: " << static_cast<int>(missileData.team) << " Strength: " << missileData.strength << std::endl;
            // ECS::Creator::createClassicMissile(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, missileData.x, missileData.y, missileData.velocityX, missileData.velocityY, missileData.team, missileData.strength);
        }
    } else {
        std::cout << "Unexpected message received player" << std::endl;
    }
}

//-----------------------------MOBS--------------------------------------------//

void Network::ClientNetwork::handleBlasterSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyMob mobData = getMob(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 305) {
            std::cout << "Entity: " << messageHeader.entity << " X: " << mobData.x << " Y: " << mobData.y << " Color: " << static_cast<int>(mobData.pos) << std::endl;
            ECS::Creator::createCancer(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, mobData.x, mobData.y);
        }
    } else {
        std::cout << "Unexpected message received player" << std::endl;
    }
}

void Network::ClientNetwork::handleCancerSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyMob mobData = getMob(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 305) {
            std::cout << "Entity: " << messageHeader.entity << " X: " << mobData.x << " Y: " << mobData.y << " Color: " << static_cast<int>(mobData.pos) << std::endl;
            ECS::Creator::createCancer(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, mobData.x, mobData.y);
        }
    } else {
        std::cout << "Unexpected message received player" << std::endl;
    }
}

void Network::ClientNetwork::handleBugSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyMob mobData = getMob(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 304) {
            std::cout << "Entity: " << messageHeader.entity << " X: " << mobData.x << " Y: " << mobData.y << " Color: " << static_cast<int>(mobData.pos) << std::endl;
            ECS::Creator::createBug(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, mobData.x, mobData.y);
        }
    } else {
        std::cout << "Unexpected message received player" << std::endl;
    }
}

void Network::ClientNetwork::handleScantSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyMob mobData = getMob(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 303) {
            std::cout << "Entity: " << messageHeader.entity << " X: " << mobData.x << " Y: " << mobData.y << " Color: " << static_cast<int>(mobData.pos) << std::endl;
            ECS::Creator::createScant(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, mobData.x, mobData.y);
        }
    } else {
        std::cout << "Unexpected message received player" << std::endl;
    }
}

void Network::ClientNetwork::handleBinkSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyMob mobData = getMob(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 302) {
            std::cout << "Entity: " << messageHeader.entity << " X: " << mobData.x << " Y: " << mobData.y << " Color: " << static_cast<int>(mobData.pos) << std::endl;
            ECS::Creator::createBink(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, mobData.x, mobData.y);
        }
    } else {
        std::cout << "Unexpected message received player" << std::endl;
    }
}

void Network::ClientNetwork::handlePataPataSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyMob mobData = getMob(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 301) {
            std::cout << "Entity: " << messageHeader.entity << " X: " << mobData.x << " Y: " << mobData.y << " Color: " << static_cast<int>(mobData.pos) << std::endl;
            ECS::Creator::createEnemyBasic(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, mobData.x, mobData.y);
        }
    } else {
        std::cout << "Unexpected message received player" << std::endl;
    }
}

//-----------------------------PLAYERS--------------------------------------------//

void Network::ClientNetwork::handlePlayerSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyAlly allyData = getAlly(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 311) {
            std::cout << "Entity: " << messageHeader.entity << " X: " << allyData.x << " Y: " << allyData.y << " Color: " << static_cast<int>(allyData.color) << std::endl;
            ECS::Creator::createPlayer(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, allyData.x, allyData.y, allyData.color);
        }
    } else {
        std::cout << "Unexpected message received player" << std::endl;
    }
}

void Network::ClientNetwork::handleAllySpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyAlly allyData = getAlly(str);
        BodyNumber footer = getBody(str);

        std::cout << "received " << footer.number << std::endl;
        if (footer.number == 312) {
            std::cout << "Ally : " << messageHeader.entity << " X: " << allyData.x << " Y: " << allyData.y << " Color: " << static_cast<int>(allyData.color) << std::endl;
            ECS::Creator::createAlly(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, allyData.x, allyData.y, allyData.color);
        }

    } else {
        std::cout << "Unexpected message received ally" << std::endl;
    }
}

//-----------------------------CONNECTION--------------------------------------------//

void Network::ClientNetwork::handleConnection(const header &messageHeader, std::string &str)
{
    if (messageHeader.codeRfc != 0)
        std::cout << "code: " << messageHeader.codeRfc << " entity: " << messageHeader.entity << std::endl;

    if (str.size() >= sizeof(BodyNumber) + sizeof(BodyNumber)) {
        BodyNumber numClients = getBody(str);
        BodyNumber footer = getBody(str);
        std::cout << "Im the player " << messageHeader.entity << " and there are " << numClients.number << " players including you." << std::endl;
        std::cout << "footer" << footer.number << std::endl;
        _indexPlayer = messageHeader.entity;
    } else {
        std::cout << "Unexpected message received connection" << std::endl;
    }
}

void Network::ClientNetwork::handleLogin(const header &messageHeader, std::string &str)
{
    static bool firstTime = false;

    if (str.size() >= sizeof(BodyNumber)) {
        BodyNumber udpPort = getBody(str);
        std::cout << "Im the player " << messageHeader.entity << " and this is the UDP port: " << udpPort.number << std::endl;

        if (!str.empty() && str.size() >= sizeof(BodyNumber)) {

            BodyNumber footer = getBody(str);
            std::cout << "Additional code: " << footer.number << std::endl;

            if (footer.number == 201 && !firstTime) {
                if (connect(_host, udpPort.number, false)) {
                    firstTime = true;
                    isConnectedUDP = true;
                    std::cout << "jme suis co en udp\n";
                } else {
                    std::cout << "jme suis pas co en udp\n";
                }
            }
        } else {
            std::cout << "Only header found" << std::endl;
        }
    } else {
        std::cout << "Unexpected message received on login" << std::endl;
    }
}

void Network::ClientNetwork::handleLogout(const header &messageHeader, std::string &str)
{
    if (messageHeader.codeRfc == 202) {
        // std::cout << "Logged out as entity: " << entity << std::endl;
    } else {
        std::cout << "Unexpected message received logout" << std::endl;
    }
}

void Network::ClientNetwork::handleMessageData(const header &messageHeader, std::string &str)
{
    auto responsehandlerIt = _responseHandlers.find(messageHeader.codeRfc);

    if (responsehandlerIt != _responseHandlers.end()) {
        responsehandlerIt->second(messageHeader, str);
    } else {
        // std::cout << "Unexecepted message received message data" << std::endl;
    }
}
