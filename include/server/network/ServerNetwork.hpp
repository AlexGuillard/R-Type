/*
** EPITECH PROJECT, 2023
** ServerNetwork.hpp
** File description:
** ServerNetwork
*/

#pragma once

#include <iostream>
#include <algorithm>
#include <thread>
#include <memory>
#include <mutex>
#include <vector>

#include "ANetwork.hpp"
#include "GameEngine/GameEngine.hpp"
#include "ECS/Containers/Registry.hpp"
#include "ECS/Containers/SparseArray.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Components/TeamComponent.hpp"
#include "ECS/Components/WaveBeamComponent.hpp"
#include "ECS/Creator.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "server/network/Participants.hpp"
#include "server/network/ServerTcp.hpp"
#include "server/network/recupInfos.hpp"

namespace Network {
    enum class Connection {
        CONNECTED,
        NOT_CONNECTED
    };
    /**
     * @brief Network class for server
     *
     */
    class ServerNetwork : public ANetwork {
    public:
        ServerNetwork(boost::asio::io_service &io_service, int portTcp, int portUdp);
        ~ServerNetwork();
        /**
         * @brief used when making the connections from the clients
         *
         */
        void tcpConnection();
        /**
         * @brief used when going into the game
         *
         */
        void udpConnection();
        // handler for asynd accept in tcp connection
        void acceptHandler(const boost::system::error_code& error, boost::asio::ip::tcp::socket socket);
        /**
         * @brief function called after receiving data
         *
         * @param error empty if finish with no error
         * @param recvd_bytes number of bytes received
         */
        void handleReceive(boost::system::error_code error, std::size_t recvd_bytes);
        /**
         * @brief function called after sending data
         *
         * @param error empty if finish with no error
         * @param recvd_bytes number of bytes received
         */
        void handleSend(boost::system::error_code error, std::size_t recvd_bytes);
        /**
         * @brief find a client in the vector by sending a id, if can not find, return ""
         *
         * @param id
         * @return std::string
         */
        bool findClient(Network::header clientData);
        /**
         * @brief function that update game when tick is finish
         *
         */
        void updateTicks();
        /**
         * @brief Get the Actual Client id
         *
         * @return std::string
         */
        std::string getActualClient() const;
        /**
         * @returns True if the game is running, false otherwise
        */
        bool isGameRunning() const;
        /**
         * @brief Runs the io service of asio
        */
        void update();
        // variable to stage number of the actuel stage
        int _stage;
    protected:
        // int for udp port to send when tcp connection
        int _portUdp;
        // store the io_service
        boost::asio::io_service &_ioService;
        /**
         * @brief variable where the client is
         *
         */
        boost::asio::ip::udp::socket _asyncSocket;
        // hmap for the list of client on the server with string of client and pair with entity of client + list of commands send
        std::unordered_map<std::string, std::pair<int, std::vector<int>>> _clients;
        // variable for the timer and the ticks
        boost::asio::deadline_timer _timer;
        // necessary for acceptation tcp clients
        boost::asio::ip::tcp::acceptor _acceptor;
        // counter for ticks in game
        std::size_t _tickCount = 0;
        // boolean to check if we are on game or not
        bool _isGame = false;
        // boolean to check if every player is in play mode
        bool _canPlay = false;
        // contain the string of client (address + port) and there udp endpoint
        std::unordered_map<std::string, boost::asio::ip::udp::endpoint> _listUdpEndpoints;
        // contain the string of client (address + port) and the id
        std::unordered_map<std::string, std::pair<int, std::vector<int>>> _ids;
        // data to send to clients
        std::string _dataToSend;
    private:
        Participants _list;
        /**
         * @brief Set the Udp Socket object
         *
         * @param port port for udp to listen to
         * @return int
         */
        int setUdpSocket(int port);
        /**
         * @brief Set the Tcp Socket object
         *
         * @param port port for udp to listen to
         * @return int
         */
        int setTcpSocket(int port);
        void handleClientData(int num);
        void SpawnMob(Info script);
        void SendClientsInfo(std::vector<Info> scriptInfo);
        void SendClientsPlay();
        void updateGame();
        void sendClientEntities();
        int pvpWin();
        void campaignEnd();
        /**
         * @brief Function that handle the event from the client and the game
         *
         * @param registry Registry of the game
         * @param positions Positions of the entities
         * @param velocities Velocities of the entities
         * @param teams Teams of the entities
         */
        void serverEventHandler(
            ECS::Containers::Registry &registry,
            ECS::Containers::SparseArray<ECS::Components::PositionComponent> &positions,
            ECS::Containers::SparseArray<ECS::Components::VelocityComponent> &velocities,
            ECS::Containers::SparseArray<ECS::Components::TeamComponent> &teams,
            ECS::Containers::SparseArray<ECS::Components::WaveBeamComponent> &waveBeamsInfos);
        void _shootMissile(
            ECS::Containers::Registry &registry,
            const ECS::Components::PositionComponent &position,
            const ECS::Components::VelocityComponent &velocity,
            const Enums::TeamGroup team);
        void _shootWaveBeam(
            ECS::Containers::Registry &registry,
            const ECS::Components::PositionComponent &position,
            const ECS::Components::VelocityComponent &velocity,
            const Enums::TeamGroup team,
            const int strength);
        void _shootWaveBeam(
            ECS::Containers::Registry &registry,
            const ECS::Components::WaveBeamComponent &waveInfo);
        void _shootBydoShot(
            ECS::Containers::Registry &registry,
            int entityId,
            const Enums::TeamGroup team
        );
        GameEngine::GameEngine _engine;
        std::unique_ptr<std::thread> _tcp;
        std::unique_ptr<std::thread> _udp;
        RecupInfo _script;
        int _typeMod = 241;
    };
}
