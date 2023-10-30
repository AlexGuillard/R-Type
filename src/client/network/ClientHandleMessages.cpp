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
#include <chrono>

//-----------------------------HANDLE MESSAGES--------------------------------------------//

void Network::ClientNetwork::initializeTCPResponsehandler()
{
    // connection
    _responseHandlersTCP[200] = [this](const header &h, std::string &s) {
        handleConnection(h, s);
        };
    _responseHandlersTCP[201] = [this](const header &h, std::string &s) {
        handleLogin(h, s);
        };
    _responseHandlersTCP[202] = [this](const header &h, std::string &s) {
        handleNewPlayer(h, s);
        };
}

void Network::ClientNetwork::initializeResponsehandler()
{
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
    _responseHandlers[322] = [this](const header &h, std::string &s) {
        handleWaveBeamSpawn(h, s);
        };
    _responseHandlers[323] = [this](const header &h, std::string &s) {
        handleBydosShotSpawn(h, s);
        };
    // entities
    _responseHandlers[331] = [this](const header &h, std::string &s) {
        handleEntityUpdate(h, s);
        };
}

//-----------------------------ENTITIES DESTRUCTION----------------------------------//

double getCurrentTime()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(now.time_since_epoch());
    return duration.count();
}

void Network::ClientNetwork::checkForDeadEntities(std::size_t tick)
{
    std::size_t maxIdleTime = 20;
    std::vector<std::size_t> listToDelete;

    for (const auto &entityTimestampPair : _entityTimestamps) {
        std::size_t entityId = entityTimestampPair.first;
        std::size_t lastUpdateTimestamp = entityTimestampPair.second;

        if (tick - lastUpdateTimestamp > maxIdleTime) {
            ECS::Entity entityToDelete = _engine.getRegistry(GameEngine::registryTypeEntities).entityFromIndex(entityId);
            _engine.getRegistry(GameEngine::registryTypeEntities).killEntity(entityToDelete);
            listToDelete.push_back(entityId);
        }
    }
    for (const auto &id : listToDelete) {
        _entityTimestamps.erase(id);
    }
    listToDelete.clear();
}

void Network::ClientNetwork::handleEntityUpdate(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(ECS::Components::PositionComponent) + sizeof(ECS::Components::VelocityComponent)
        + sizeof(BodyNumber) + sizeof(BodyNumber)) {
        ECS::Components::PositionComponent positionData = getPosition(str);
        ECS::Components::VelocityComponent velocityData = getVelocity(str);
        BodyNumber tick = getBody(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 331) {
            // std::cout << "entityToUpdate: " << messageHeader.entity << " X: " << velocityData.x << " Y: " << velocityData.y << std::endl;
            ECS::Entity entityToUpdate = _engine.getRegistry(GameEngine::registryTypeEntities).entityFromIndex(messageHeader.entity);

            _engine.getRegistry(GameEngine::registryTypeEntities).emplaceComponent<ECS::Components::PositionComponent>(entityToUpdate, positionData.x, positionData.y); //position
            _engine.getRegistry(GameEngine::registryTypeEntities).emplaceComponent<ECS::Components::VelocityComponent>(entityToUpdate, velocityData.x, velocityData.y); //velocity
            _entityTimestamps[messageHeader.entity] = tick.number;
            checkForDeadEntities(tick.number);
        }

    } else {
        str.clear();
    }
}

//-----------------------------MISSILES--------------------------------------------//

void Network::ClientNetwork::handleClassicMissileSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyMissile) + sizeof(BodyNumber)) {
        bodyMissile missileData = getMissile(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 321) {
            ECS::Creator::createMissile(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, missileData.x, missileData.y, missileData.team);
        }
    } else {
        str.clear();
    }
}

void Network::ClientNetwork::handleWaveBeamSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyMissile) + sizeof(BodyNumber)) {
        bodyMissile missileData = getMissile(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 322) {
            ECS::Creator::createWaveBeam(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, missileData.x, missileData.y, missileData.team, missileData.strength);
        }
    } else {
        str.clear();
    }
}

void Network::ClientNetwork::handleBydosShotSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyMissile) + sizeof(BodyNumber)) {
        bodyMissile missileData = getMissile(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 323) {
            // ECS::Creator::createBydoShot(_engine.getRegistry(GameEngine::registryTypeEntities), missileData.x, missileData.y, missileData.velocityX, missileData.velocityY, missileData.team);
        }
    } else {
        str.clear();
    }
}

//-----------------------------MOBS--------------------------------------------//

void Network::ClientNetwork::handleBlasterSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyMob mobData = getMob(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 306) {
            ECS::Creator::createBlaster(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, mobData.x, mobData.y);
        }
    } else {
        str.clear();
    }
}

void Network::ClientNetwork::handleCancerSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyMob mobData = getMob(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 305) {
            ECS::Creator::createCancer(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, mobData.x, mobData.y);
        }
    } else {
        str.clear();
    }
}

void Network::ClientNetwork::handleBugSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyMob mobData = getMob(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 304) {
            ECS::Creator::createBug(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, mobData.x, mobData.y);
        }
    } else {
        str.clear();
    }
}

void Network::ClientNetwork::handleScantSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyMob mobData = getMob(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 303) {
            ECS::Creator::createScant(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, mobData.x, mobData.y);
        }
    } else {
        str.clear();
    }
}

void Network::ClientNetwork::handleBinkSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyMob mobData = getMob(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 302) {
            ECS::Creator::createBink(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, 600, mobData.y);
        }
    } else {
        str.clear();
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
        str.clear();
    }
}

//-----------------------------PLAYERS--------------------------------------------//

void Network::ClientNetwork::handlePlayerSpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyAlly allyData = getAlly(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 311) {
            ECS::Creator::createPlayer(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, allyData.x, allyData.y, allyData.color);
        }
    } else {
        str.clear();
    }
}

void Network::ClientNetwork::handleAllySpawn(const header &messageHeader, std::string &str)
{
    if (str.size() >= sizeof(bodyAlly) + sizeof(BodyNumber)) {
        bodyAlly allyData = getAlly(str);
        BodyNumber footer = getBody(str);

        if (footer.number == 312) {
            ECS::Creator::createAlly(_engine.getRegistry(GameEngine::registryTypeEntities), messageHeader.entity, allyData.x, allyData.y, allyData.color);
        }

    } else {
        str.clear();
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

void Network::ClientNetwork::handleNewPlayer(const header &messageHeader, std::string &str)
{
    if (messageHeader.codeRfc == 202) {
        std::cout << "new player " << std::endl;
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

void Network::ClientNetwork::handleTCPMessageData(const header &messageHeader, std::string &str)
{
    auto responsehandlerIt = _responseHandlersTCP.find(messageHeader.codeRfc);

    if (responsehandlerIt != _responseHandlersTCP.end()) {
        responsehandlerIt->second(messageHeader, str);
    } else {
        // std::cout << "Unexecepted message received message data" << std::endl;
    }
}
