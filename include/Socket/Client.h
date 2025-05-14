   
#pragma once
#include "Utils.h"
#include "Application.h"
namespace JuuPiero {
class Client {
    
public:
    ~Client();
    void ShutDown();
    void Run();
    static Client* GetInstance();
    void Send(std::string message);
    void OnConnected(json data);

    // void OnUpdate(std::string data);
    // void OnLoginSuccess();
    // void OnLogoutSuccess();

private:
    Client();
    void ReceiveMessages();

private:

    uint32_t m_Id;

    static Client* s_Instance;
    WSADATA m_WsaData;
    SOCKET m_ClientSocket = INVALID_SOCKET;
    struct sockaddr_in m_ServerAddr;
    
    std::thread m_ReceiveThread;
    uint32_t m_ServerPort;
    const char* m_ServerAddress;
    int iResult;

    bool m_IsRunning;
    // json responseData;
};
}