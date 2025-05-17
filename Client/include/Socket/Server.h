#pragma once
#include "Utils.h"

namespace JuuPiero {

class Server {
public:
    static Server* GetInstance();
    void ShutDown();
    void Run();
    ~Server();
private:
    Server();
    static Server* s_Insntance;
    WSADATA m_WsaData;
    SOCKET m_ListenSocket;
    sockaddr_in m_ServerAddr;
    uint32_t m_Port;
    int iResult;

    std::unordered_map<std::string, SOCKET> m_Clients; 
};
}