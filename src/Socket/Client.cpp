#include "Socket/Client.h"
#include "Socket/ResponseCode.h"

#include "Utils.h"

namespace JuuPiero {
Client* Client::s_Instance = nullptr;
Client::Client(): m_ServerPort(8386), m_ServerAddress("127.0.0.1") {

    int iResult = WSAStartup(MAKEWORD(2, 2), &m_WsaData);
    if (iResult != 0) {
        std::cout << "WSAStartup failed: " << iResult << std::endl;
        ShutDown();
        return;
    }
    m_ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_ClientSocket == INVALID_SOCKET) {
        std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
        ShutDown();
        return;
    }

    m_ServerAddr.sin_family = AF_INET;
    m_ServerAddr.sin_addr.s_addr = inet_addr(m_ServerAddress); // Địa chỉ IP của máy chủ trong mạng cục bộ
    m_ServerAddr.sin_port = htons(m_ServerPort);

    int connectResult = connect(m_ClientSocket, (struct sockaddr*)&m_ServerAddr, sizeof(m_ServerAddr));
    if (connectResult == SOCKET_ERROR) {
        std::cout << "connect failed: " << WSAGetLastError() << std::endl;
        ShutDown();
        return;
    }

    m_IsRunning = true;
}

Client* Client::GetInstance() {
    if (s_Instance == nullptr) {
        s_Instance = new Client();
    }
    return s_Instance;
}
void Client::Run() {
    m_ReceiveThread = std::thread(&Client::ReceiveMessages, this);
    m_ReceiveThread.detach();
}

void Client::ReceiveMessages() {
    std::cout << "Connected to server succesfully" << std::endl;
    char recvbuf[DEFAULT_BUFLEN];
    int responseCode = -1;
    
    while(m_IsRunning) {
        iResult = recv(m_ClientSocket, recvbuf, DEFAULT_BUFLEN, 0);
        if (iResult > 0) {
            recvbuf[iResult] = '\0';
            std::cout << "Server Response: " << std::endl;
            std::cout << recvbuf << std::endl;

            // json response = json::parse(std::string(recvbuf));
            // responseCode = response["response_code"];
            // switch (responseCode) {
            //     case ResponseCode::CONNECTED:
            //         OnConnected(response["data"]);
            //         break;
            // }
        } 
        else if (iResult == 0) {
            std::cout << "Connection closed by server" << std::endl;
            break;
        } 
        else {
            std::cout << "recv failed: " << WSAGetLastError() << std::endl;
            break;
        }
    };
}

void Client::Send(std::string message) {
    // message = std::to_string(m_Id) + " " + message;  
    send(m_ClientSocket, message.c_str(), message.size(), 0);
}


void Client::ShutDown() {
    std::cout << "Close socket" << std::endl;
    closesocket(m_ClientSocket);
    WSACleanup();
    m_IsRunning = false;
    delete s_Instance;
    s_Instance = nullptr;
}


// void Client::OnUpdate(std::string data) {

// }

void Client::OnConnected(json data) {
    m_Id = data["id"];
    std::cout << "Your client id : " << m_Id << std::endl;
    
}


Client::~Client() {}
    
}