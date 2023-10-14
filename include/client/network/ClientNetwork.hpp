/*
** EPITECH PROJECT, 2023
** ClientNetwork.hpp
** File description:
** ClientNetwork
*/

#ifndef CLIENTNETWORK_HPP_
#define CLIENTNETWORK_HPP_
#include "ANetwork.hpp"
#include <iostream>
#include "Error.hpp"
#include <map>
#include <functional>
#include <memory>
#include <queue>

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
        using ResponseHandler = std::function<void (const std::string&)>;
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
        void handleConnection(const std::string &message);
        /**
         * @brief Handle the Login from server
         *
         * @param message message from the server
         */
        void handleLogin(const std::string &message);
        /**
         * @brief Handle the Logout from server
         *
         * @param message message from the server
         */
        void handleLogout(const std::string &message);

        /**
         * @brief Get the Instance object
         *
         * @return ClientNetwork&
         */
        static ClientNetwork &getInstance();
        /**
         * @brief Get the Instance object
         *
         * @param io_service
         * @param host
         * @param port
         * @return ClientNetwork&
         */
        static ClientNetwork &getInstance(boost::asio::io_service &io_service, const std::string &host, int port);
        /**
         * @brief Construct a new Client Network object with parameters
         *
         * @param io_service
         * @param host
         * @param port
         */
        ClientNetwork(boost::asio::io_service &io_service, const std::string &host, int port);
        /**
         * @brief Construct a new Client Network object without parameters
         *
         */
        ClientNetwork();
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
        boost::asio::ip::udp::socket& getUDPSocket();
        /**
         * @brief Enqueue a received message
         *
         * @param message
         */
        void enqueueReceivedMessage(const std::string& message);
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
        boost::asio::ip::tcp::socket& getTCPSocket();
        /**
         * @brief Handle the TCP data received
         *
         * @param error error
         * @param recvd_bytes size of the data
         * @param tcpsocket socket
         */
        void handleTCPData(const boost::system::error_code& error, std::size_t recvd_bytes, boost::asio::ip::tcp::socket &tcpsocket);
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
        std::map<std::string, ResponseHandler> _responseHandlers;
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
    };
}

#endif /* !CLIENTNETWORK_HPP_ */
