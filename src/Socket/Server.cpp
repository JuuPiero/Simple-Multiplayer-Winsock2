#include "Socket/Server.h"
#include "Utils.h"

namespace JuuPiero {
Server* Server::s_Insntance = nullptr;

Server::Server(): m_Port(8386) {
    // Initialize Winsock
    int iResult = WSAStartup(MAKEWORD(2, 2), &m_WsaData);
    if (iResult != 0) {
        std::cout << "WSAStartup failed: " << iResult << std::endl;
        ShutDown();
        return;
    }
    // Create a socket for listening
    m_ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_ListenSocket == INVALID_SOCKET) {
        std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
        ShutDown();
        return;
    }

    // Setup server address
    m_ServerAddr.sin_family = AF_INET;
    m_ServerAddr.sin_addr.s_addr = INADDR_ANY; //lắng nghe mọi máy từ mạng cục bộ
    m_ServerAddr.sin_port = htons(m_Port);

    // Bind socket
    iResult = bind(m_ListenSocket, (struct sockaddr*)&m_ServerAddr, sizeof(m_ServerAddr));
    if (iResult == SOCKET_ERROR) {
        std::cout << "bind failed: " << WSAGetLastError() << std::endl;
        ShutDown();
        return;
    }
    // Listen on socket
    iResult = listen(m_ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        std::cout << "listen failed: " << WSAGetLastError() << std::endl;
        closesocket(m_ListenSocket);
        WSACleanup();
        return;
    }
    std::cout << "Server listening on port: " <<  m_Port << std::endl;
}

Server* Server::GetInstance() {
    if (s_Insntance == nullptr) {
        s_Insntance = new Server();
    }
    return s_Insntance;
}
void Server::ShutDown() {
    closesocket(m_ListenSocket);
    WSACleanup();
    m_ClientSockets.clear();
    delete s_Insntance;
    s_Insntance = nullptr;
    std::cout << "Close Socket" << std::endl;
}

void Server::Run() {
    // Accept a client socket
    // SOCKET clientSocket;
    // clientSocket = accept(m_ListenSocket, nullptr, nullptr);
    // if (clientSocket == INVALID_SOCKET) {
    //     std::cout << "accept failed: " << WSAGetLastError() << std::endl;
    //     closesocket(m_ListenSocket);
    //     WSACleanup();
    //     return;
    // }
    // uint32_t id = GetId();
    // m_ClientSockets[id] = clientSocket;
    // std::thread handlerThread(&Server::ClientHandler, this, clientSocket, id);
    // handlerThread.detach();
   
    std::thread acceptThread([this]() {
        while (true) {
            SOCKET clientSocket = accept(m_ListenSocket, nullptr, nullptr);
            if (clientSocket != INVALID_SOCKET) {
                uint32_t id = GetId();
                m_ClientSockets[id] = clientSocket;
                std::thread handlerThread(&Server::ClientHandler, this, clientSocket, id);
                handlerThread.detach();
            }
        }
    });
    acceptThread.detach();  // Chạy thread tiếp nhận kết nối
}

void Server::ClientHandler(SOCKET clientSocket, uint32_t clientSocketId) {
    
    char recvbuf[DEFAULT_BUFLEN];
    std::cout << "A client connected to server: " << clientSocketId << ": "  << clientSocket << std::endl;

  

    do {
        iResult = recv(clientSocket, recvbuf, DEFAULT_BUFLEN, 0);
        if (iResult > 0) {
            std::cout << "A client connected to server: " << clientSocket << std::endl;
            recvbuf[iResult] = '\0';
            //parse data from client
            // std::istringstream iss(recvbuf);
            // json requestData = json::parse(std::string(recvbuf));
            std::cout << "message from client: " << std::endl;
            // std::cout << requestData.dump(4) << std::endl;
            // int command = requestData["command"];

            // if(command == Command::LOGIN) {
            //     std::string username = requestData["data"]["username"];
            //     std::string password = requestData["data"]["password"];
            //     OnUserLogin(clientSocketId, username, password);
            // }
            // else if(command == Command::SIGNUP) {
            //     std::string username = requestData["data"]["username"];
            //     std::string password = requestData["data"]["password"];
            //     OnUserSignup(clientSocketId, username, password);
            // }
            
        } else if (iResult == 0) {
            std::cout << "Connection closed by client" << std::endl;
        } else {
            std::cout << "A client disconnected: " << WSAGetLastError() << std::endl;
            // spdlog::error("A client disconnected : {}", WSAGetLastError());
        }
    } while (iResult > 0);

    closesocket(clientSocket);
    m_ClientSockets.erase(clientSocketId);
}

Server::~Server() {
    ShutDown();
}
}