/*
** EPITECH PROJECT, 2023
** ClientNetwork.hpp
** File description:
** ClientNetwork
*/

#ifndef CLIENTNETWORK_HPP_
#define CLIENTNETWORK_HPP_
#include <optional>
#include "ANetwork.hpp"
#include <iostream>
#include "Error.hpp"
#include <map>
#include <functional>
#include <memory>
#include <queue>
#include "GameEngine/GameEngine.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"

namespace Network {

    /**
     * @brief Enum used to know the movement of the player on the server
     *
     */
    enum class Movement {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    /**
     * @brief Enum used to know the action of the player on the server
     *
     */
    enum class Action {
        SHOOT,
        DROP
    };
    /**
     *@brief ClientNetwork class use to communicate with the server
     *
     */
    class ClientNetwork : public ANetwork {

    public:
        /**
         * @brief Destroy the Client Network object
         *
         */
        ~ClientNetwork();
        /**
         * @brief This function is used to receive data from the server
         *
         * @param error
         * @param recvd_bytes
         */
        void handleReceive(boost::system::error_code error, std::size_t recvd_bytes);
        /**
         * @brief This function is used to send data to the server
         *
         * @param error
         * @param recvd_bytes
         */
        void handleSend(boost::system::error_code error, std::size_t recvd_bytes);
        /**
         * @brief This function is used to send a hello to the server to connect to it
         *
         */
        void sendHello();
        /**
         * @brief This function is used to send a movement from the player to the server
         *
         * @param movement
         */
        void sendMovement(Movement movement);
        /**
         * @brief This function is used to send an action from the player to the server
         *
         * @param action
         */
        void sendAction(Action action);
        /**
         * @brief This function is used to connect to the server if the server return 301 then the connection and return true else false
         *
         * @param host
         * @param port
         */
        bool connect(const std::string &host, int port, bool isTCP);
        /**
         * @brief Is contained on the map of funciton to use the pointer on function
         *
         */
        using ResponseHandler = std::function<void(const std::string &)>;
        /**
         * @brief Initialize the function to use the pointer to function
         *
         */
        void initializeResponsehandler();
        /**
         * @brief Handle the Connection from server
         *
         * @param message message from the server
         */
        void handleConnection(const header &messageHeader, std::string &str);
        /**
         * @brief Handle the Login from server
         *
         * @param message message from the server
         */
        void handleLogin(const header &messageHeader, std::string &str);
        /**
         * @brief Handle the Logout from server
         *
         * @param message message from the server
         */
        void handleLogout(const header &messageHeader, std::string &str);
        /**
         * @brief Handle the player spawn
         *
         * @param messageHeader header
         * @param str string from server
         */
        void handlePlayerSpawn(const header &messageHeader, std::string &str);
        /**
         * @brief handle the fact of create pata pata ennemies when the server said it
         *
         * @param messageHeader
         * @param str
         */
        void handlePataPataSpawn(const header &messageHeader, std::string &str);
        /**
         * @brief handle the fact of create bink ennemies when the server said it
         *
         * @param messageHeader
         * @param str
         */
        void handleBinkSpawn(const header &messageHeader, std::string &str);
        /**
         * @brief handle the fact of create scant ennemies when the server said it
         *
         * @param messageHeader
         * @param str
         */
        void handleScantSpawn(const header &messageHeader, std::string &str);
        /**
         * @brief handle the fact of create bug ennemies when the server said it
         *
         * @param messageHeader
         * @param str
         */
        void handleBugSpawn(const header &messageHeader, std::string &str);
        /**
         * @brief handle the fact of create cancer ennemies when the server said it
         *
         * @param messageHeader
         * @param str
         */
        void handleCancerSpawn(const header &messageHeader, std::string &str);
        /**
         * @brief handle the fact of create blaster ennemies when the server said it
         *
         * @param messageHeader
         * @param str
         */
        void handleBlasterSpawn(const header &messageHeader, std::string &str);
        /**
         * @brief handle the fact of creat allies when the server said it
         *
         * @param messageHeader
         * @param str
         */
        void handleAllySpawn(const header &messageHeader, std::string &str);
        /**
         * @brief handle the fact of create a classic missile when the server said it
         *
         * @param messageHeader
         * @param str
         */
        void handleClassicMissileSpawn(const header &messageHeader, std::string &str);
        /**
         * @brief handle the fact of create a wave missile when the server said it
         *
         * @param messageHeader
         * @param str
         */
        void handleWaveBeamSpawn(const header &messageHeader, std::string &str);
        /**
         * @brief handle the fact of create a bydos missile when the server said it
         *
         * @param messageHeader
         * @param str
         */
        void handleBydosShotSpawn(const header &messageHeader, std::string &str);
        /**
         * @brief Get the Instance object
         *
         * @return ClientNetwork&
         */
        static ClientNetwork &getInstance();
        /**
         * @brief Get the Instance object
         *
         * @return ClientNetwork&
         */
        static ClientNetwork &getInstance(GameEngine::GameEngine &engine);
        /**
         * @brief Construct a new Client Network object without parameters
         *
         */
        ClientNetwork(GameEngine::GameEngine &engine);
        /**
         * @brief Function to put at the end of the loop to handle the network, it make a reset and poll for the ioService
         *
         */
        void handleNetwork();
        /**
         * @brief stop the ioService
         *
         */
        void stopIOService();
        /**
         * @brief Get the Socket object
         *
         * @return const boost::asio::ip::udp::socket&
         */
        boost::asio::ip::udp::socket &getUDPSocket();
        /**
         * @brief Enqueue a received message
         *
         * @param message
         */
        void enqueueReceivedMessage(const std::string &message);
        /**
         * @brief Establish a TCP connection
         *
         * @return true
         * @return false
         */
        bool connectTCP(const std::string &host, int port);
        /**
         * @brief Get the TCP Socket object
         *
         * @return boost::asio::ip::tcp::socket&
         */
        boost::asio::ip::tcp::socket &getTCPSocket();
        /**
         * @brief Handle the TCP data received
         *
         * @param error error
         * @param recvd_bytes size of the data
         * @param tcpsocket socket
         */
        void handleTCPData(const boost::system::error_code &error, std::size_t recvd_bytes, boost::asio::ip::tcp::socket &tcpsocket);
        /**
         * @brief Start the async receive for tcp connection
         *
         * @param tcpsocket socket
         */
        void startAsyncReceiveTCP(boost::asio::ip::tcp::socket &tcpsocket);
        /**
         * @brief Get the Header object
         *
         * @param str string from server
         * @return header
         */
        header getHeader(std::string &str);
        /**
         * @brief Get the Ally object
         *
         * @param str
         * @return bodyAlly
         */
        bodyAlly getAlly(std::string &str);
        /**
         * @brief send a 201 to the server on binary format with a header struct
         *
         */
        void send201();
        /**
         * @brief handle messages from the server and call the right function attributed to the header rfc code
         *
         * @param messageHeader
         * @param str
         */
        void handleMessageData(const header &messageHeader, std::string &str);
        //Use to know if the client is connected to the server
        bool isConnectedUDP = false;
        /**
         * @brief Get the Local UDP Endpoint object
         *
         * @return boost::asio::ip::udp::endpoint
         */
        boost::asio::ip::udp::endpoint getLocalUDPEndpoint();
        /**
         * @brief Get the Local TCP Endpoint object
         *
         * @return boost::asio::ip::tcp::endpoint
         */
        boost::asio::ip::tcp::endpoint getLocalTCPEndpoint();
        /**
         * @brief Get the Body object
         *
         * @param str
         * @return Network::BodyNumber
         */
        Network::BodyNumber getBody(std::string &str);
        /**
         * @brief Get the Mob object
         *
         * @param str
         * @return Network::bodyMob
         */
        Network::bodyMob getMob(std::string &str);
        /**
         * @brief Get the Missile object
         *
         * @param str
         * @return Network::bodyMissile
         */
        Network::bodyMissile getMissile(std::string &str);
        /**
         * @brief Set the Engine object
         *
         * @param engine
         */
        void setEngine(GameEngine::GameEngine &engine);
        /**
         * @brief handle he fact of despawn entities from the game
         *
         * @param messageHeader
         * @param str
         */
        void handleEntityUpdate(const header &messageHeader, std::string &str);
        /**
         * @brief Get the Velocity object
         *
         * @param str
         * @return ECS::Components::VelocityComponent
         */
        ECS::Components::VelocityComponent getVelocity(std::string &str);
        /**
         * @brief Get the Position object
         *
         * @param str
         * @return ECS::Components::PositionComponent
         */
        ECS::Components::PositionComponent getPosition(std::string &str);

    private:
        //Port of the server
        int _port;
        //Host of the server
        std::string _host;
        //Used to manage asynchrous services
        boost::asio::io_service _ioService;
        //Socket of the client
        boost::asio::ip::udp::socket _socket;
        //Data received
        std::string _dataReceived;
        //Map to use the pointer on function
        std::map<int, std::function<void(const header &, std::string &)>> _responseHandlers;
        //Stock class for SingleTon
        static std::unique_ptr<ClientNetwork> _instance;
        //Message to send
        std::queue<std::string> _messagesToSend;
        //Mutex to lock the queue
        std::mutex _mutex;
        //Queue of received messages
        std::queue<std::string> _receivedMessages;
        //Socket of the tcp
        boost::asio::ip::tcp::socket _tcpSocket;
        //Size of the header of the message
        static constexpr std::size_t HEADER_SIZE = sizeof(header);
        //The Index of the player send by server for the color etc... (between 0 and 3)
        int _indexPlayer = -1;
        //Engine of the game
        GameEngine::GameEngine &_engine;
    };
}

#endif /* !CLIENTNETWORK_HPP_ */
