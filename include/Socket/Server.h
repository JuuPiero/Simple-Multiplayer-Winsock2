#pragma once
#include "Utils.h"

namespace JuuPiero {

class Server {
public:
    static Server* GetInstance();
    void ShutDown();
    void Run();
    ~Server();
    Server();
    // void Listen(int port);
private:
    void ClientHandler(SOCKET clientSocket, uint32_t clientSocketId);
private:
    static Server* s_Insntance;
    WSADATA m_WsaData;
    SOCKET m_ListenSocket;
    sockaddr_in m_ServerAddr;
    uint32_t m_Port;
    int iResult;
    std::unordered_map<uint32_t, SOCKET> m_ClientSockets;
};
}