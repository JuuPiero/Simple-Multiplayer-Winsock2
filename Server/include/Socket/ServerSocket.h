#pragma once
#include <iostream>
#include <WinSock2.h>
#include <functional>
#include <unordered_map>
#include <mutex>
#include <thread>
#include "Player.h"

namespace JuuPiero {
class ServerSocket {
public:
    ServerSocket(std::string ip = "127.0.0.1");
    ~ServerSocket();
    void Listen(uint32_t port, std::function<void()> callback);
    void ClientHandler(uint32_t clientSocketId);
    inline uint32_t NewId() {
        static uint32_t clientIdCounter = 0;
        return ++clientIdCounter;
    }

    void Send(uint32_t clientSocketId, const std::string& message);
    void Emit(const std::string& message);

    void OnConnect(uint32_t clientSocketId);
    // void Emit(std::function<void(std::string)> callback);

private:
    

    std::mutex m_ClientsMutex;
    std::string m_IpAddress;
    uint32_t m_Port;
    WSADATA m_WsaData;
    SOCKET m_ListenSocket;
    sockaddr_in m_ServerAddr;

    std::unordered_map<uint32_t, SOCKET> m_Clients;
    std::unordered_map<uint32_t, Player> m_Players;

};

}