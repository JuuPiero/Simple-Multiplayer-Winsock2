#include "Socket/SocketClient.h"
#include "Socket/ResponseCode.h"

#include "Utils.h"

namespace JuuPiero {
SocketClient* SocketClient::s_Instance = nullptr;

SocketClient::SocketClient() {
    int result = WSAStartup(MAKEWORD(2, 2), &m_WsaData);
    if (result != 0) {
        std::cout << "WSAStartup failed: " << result << std::endl;
    }
}

SocketClient* SocketClient::GetInstance() {
    if (s_Instance == nullptr) {
        s_Instance = new SocketClient();
    }
    return s_Instance;
}

SocketClient::~SocketClient() {
    // Disconnect();
    WSACleanup();
}


bool SocketClient::Connect(const std::string& ip, uint16_t port) {
    m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_Socket == INVALID_SOCKET) {
        std::cout << "Socket creation failed: " << WSAGetLastError() << std::endl;
        return false;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr);
    serverAddr.sin_port = htons(port);

    int result = connect(m_Socket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    if (result == SOCKET_ERROR) {
        std::cout << "Connect failed: " << WSAGetLastError() << std::endl;
        closesocket(m_Socket);
        return false;
    }

    m_ReceiveThread = std::thread(&SocketClient::ReceiveLoop, this);
    return true;
}

void SocketClient::On(const std::string& eventName, std::function<void(const std::string&)> callback) {
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_EventHandlers[eventName] = callback;
}

void SocketClient::Emit(const std::string& message) {
    send(m_Socket, message.c_str(), message.size(), 0);
}

void SocketClient::Disconnect() {
    closesocket(m_Socket);
    if (m_ReceiveThread.joinable()) {
        m_ReceiveThread.join();
    }
    delete s_Instance;
    // s_Instance = nullptr;
}

void SocketClient::ReceiveLoop() {
    char buffer[2048];
    while (true) {
        int result = recv(m_Socket, buffer, 2047, 0);
        if (result > 0) {
            buffer[result] = '\0';
            std::cout << buffer << std::endl;
            json response;
            try {
                response = json::parse(std::string(buffer));
            }
            catch(const std::exception& e) {
                continue;
            }
            
            ResponseCode responseCode = response["response_code"];

            switch (responseCode) {
                case ResponseCode::UPDATE: {
                    // m_Players.clear();
                    for (auto &player : response["players"]) {
                        std::lock_guard<std::mutex> lock(m_Mutex);
                        json position = player["position"];
                        uint32_t id = player["id"];
                        std::cout << position.dump() << std::endl;
                        int x = position["x"];
                        int y = position["y"];
                        m_Players[id].SetSize(50, 100);
                        if(m_Players[id].GetId() == 0) {
                            m_Players[id].SetId(id);
                        }
                        m_Players[id].SetPosition(x, y);
                        // Player newPlayer = Player{x, y, 50, 100};
                        // newPlayer.SetId(id);
                        // m_Players[id] = newPlayer;
                    }
                    break;
                }
                case ResponseCode::CONNECTED: 
                    m_Id = response["id"];
                    std::cout << "Client id dc cap la: " << m_Id << std::endl;
                    break;
            }

            // Giả định: tin nhắn có định dạng: "eventName:data"
            // auto delimiterPos = msg.find(':');
            // if (delimiterPos != std::string::npos) {
            //     std::string eventName = msg.substr(0, delimiterPos);
            //     std::string data = msg.substr(delimiterPos + 1);

            //     std::lock_guard<std::mutex> lock(m_Mutex);
            //     if (m_EventHandlers.count(eventName)) {
            //         m_EventHandlers[eventName](data);
            //     }
            // }
        } else if (result == 0) {
            std::cout << "Server closed connection." << std::endl;
            // Disconnect();
            break;
        } else {
            std::cout << "recv failed: " << WSAGetLastError() << std::endl;
            break;
        }
    }
    Disconnect();
    // m_Running = false;
}

}