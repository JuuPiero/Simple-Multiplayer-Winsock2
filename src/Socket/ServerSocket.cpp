#include "Socket/ServerSocket.h"
#include "Socket/RequestCode.h"
#include "Socket/ResponseCode.h"
#include "Utils.h"
#include "Player.h"



namespace JuuPiero {

ServerSocket::ServerSocket(std::string ip): m_IpAddress(ip) {
    int iResult = WSAStartup(MAKEWORD(2, 2), &m_WsaData);
    if(iResult != 0) {
        std::cout << "WSAStartup failed " << iResult << std::endl;
        return;
    }

    m_ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(m_ListenSocket == INVALID_SOCKET) {
        std::cout << "Error at socket(): " + WSAGetLastError() << std::endl;
        return;
    }
}

void ServerSocket::Listen(uint32_t port, std::function<void()> callback) {
    m_Port = port;
    m_ServerAddr.sin_family = AF_INET;
    m_ServerAddr.sin_addr.s_addr = INADDR_ANY; //lắng nghe mọi máy từ mạng cục bộ
    m_ServerAddr.sin_port = htons(m_Port);

    // Bind socket
    int result = bind(m_ListenSocket, (struct sockaddr*)&m_ServerAddr, sizeof(m_ServerAddr));
    if (result == SOCKET_ERROR) {
        std::cout << "bind failed: " << WSAGetLastError() << std::endl;
        return;
    }
    // Listen on socket
    result = listen(m_ListenSocket, SOMAXCONN);
    if (result == SOCKET_ERROR) {
        std::cout << "listen failed: " << WSAGetLastError() << std::endl;
        return;
    }

    if(callback != nullptr) {
        callback();
    }

    // std::thread runThread()


    std::thread runThread([this]() {
        while (true) {
            SOCKET clientSocket = accept(m_ListenSocket, nullptr, nullptr); // blocking
            if (clientSocket != INVALID_SOCKET) {
                std::lock_guard<std::mutex> lock(m_ClientsMutex);
                uint32_t id = NewId();
                m_Clients[id] = clientSocket;
                Player newPlayer = Player(0, 0, 50, 100);
                m_Players[id] = newPlayer;
                // OnConnect(id);
                std::thread handlerThread(&ServerSocket::ClientHandler, this, id);
                handlerThread.detach();
            }
        }
    });
    runThread.detach();
}

ServerSocket::~ServerSocket() {
    closesocket(m_ListenSocket);
    WSACleanup();
}

void ServerSocket::OnConnect(uint32_t clientSocketId) {
    json response;
    response["response_code"] = ResponseCode::CONNECTED;
    response["id"] = clientSocketId;
    Send(clientSocketId, response.dump());

    {
        json response;
        response["response_code"] = ResponseCode::UPDATE;
        response["players"] = json::array();
        for (auto &p : m_Players) {
            response["players"].push_back({
                {"id", p.first},
                {"position", {
                    {"x", p.second.GetPosition().x},
                    {"y", p.second.GetPosition().y},
                }}
            });
        }
        Emit(response.dump());
    }
}

void ServerSocket::ClientHandler(uint32_t clientSocketId) {
    SOCKET clientSocket = m_Clients[clientSocketId];
    std::cout << "A client connected to server: " << clientSocketId << ": "  << clientSocket << std::endl;
    OnConnect(clientSocketId);

    char buffer[2048];
    while (true) {
        int result = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (result > 0) {
            buffer[result] = '\0';
            std::cout << buffer << std::endl;
            json request;
            try {
                request = json::parse(std::string(buffer));
            }
            catch(const std::exception& e)
            {
                continue;
            }
            
           
            RequestCode resquestCode = request["request_code"];
            
            switch (resquestCode) {
                case RequestCode::MOVE: {
                    json position = request["position"];
                    std::cout << position.dump() << std::endl;
                    m_Players[clientSocketId].SetPosition(position["x"], position["y"]);
                    {
                        // std::lock_guard<std::mutex> lock(m_ClientsMutex);
                        json response;
                        response["response_code"] = ResponseCode::UPDATE;
                        response["players"] = json::array();
                        for (auto &p : m_Players) {
                            response["players"].push_back({
                                {"id", p.first},
                                {"position", {
                                    {"x", p.second.GetPosition().x},
                                    {"y", p.second.GetPosition().y},
                                }}
                            });
                        }
                        Emit(response.dump());
                    }
                    // std::cout << "Player " << clientSocketId << " DI chuyen" << std::endl;
                    break;
                }
            }
            
        }
        else if (result == 0) {
            // std::lock_guard<std::mutex> lock(m_ClientsMutex);
            std::cout << "disconnect: " << WSAGetLastError() << std::endl;
            closesocket(clientSocket);
            m_Clients.erase(clientSocketId);
            m_Players.erase(clientSocketId);
            break;
        }
        else {
            // std::lock_guard<std::mutex> lock(m_ClientsMutex);
            std::cout << "recv failed: " << WSAGetLastError() << std::endl;
            closesocket(clientSocket);
            m_Clients.erase(clientSocketId);
            m_Players.erase(clientSocketId);
            break;
        }
    
        // std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    // closesocket(clientSocket);
    // m_Clients.erase(clientSocketId);
    // m_Players.erase(clientSocketId);
    // OnDisConnect(clientSocketId);
}

void ServerSocket::Send(uint32_t clientSocketId, const std::string& message) {
    std::lock_guard<std::mutex> lock(m_ClientsMutex);
    SOCKET clientSocket = m_Clients[clientSocketId];
    int result = send(clientSocket, message.c_str(), message.length(), 0);
    if (result == SOCKET_ERROR) {
        std::lock_guard<std::mutex> lock(m_ClientsMutex);

        std::cout << "Send failed: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        m_Clients.erase(clientSocketId);
        m_Players.erase(clientSocketId);
    }
}

void ServerSocket::Emit(const std::string& message) {
    for (auto &client : m_Clients) {
        Send(client.first, message);
    }
}

}