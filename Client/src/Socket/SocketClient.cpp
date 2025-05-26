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
    m_Running = true;
    m_ReceiveThread = std::thread(&SocketClient::ReceiveLoop, this);
    return true;
}


void SocketClient::Emit(const std::string& message) {
    send(m_Socket, message.c_str(), message.size(), 0);
}

void SocketClient::Disconnect() {
    m_Running = false;
    shutdown(m_Socket, SD_BOTH);  // <-- Giúp recv() thoát nhanh
    closesocket(m_Socket);

    if (m_ReceiveThread.joinable() && std::this_thread::get_id() != m_ReceiveThread.get_id()) {
        m_ReceiveThread.join();
    }

    delete s_Instance;
    s_Instance = nullptr;
}

void SocketClient::ReceiveLoop() {
    char buffer[2048];
    while (m_Running) {
        int result = recv(m_Socket, buffer, 2047, 0);
        
        if (result > 0) {
          
            buffer[result] = '\0';
            std::cout << buffer << std::endl;
            m_Leftover += buffer;

            size_t pos;
            while ((pos = m_Leftover.find('\n')) != std::string::npos) {
                std::string message = m_Leftover.substr(0, pos);
                m_Leftover.erase(0, pos + 1);

                try {
                    json response = json::parse(message);

                    ResponseCode responseCode = response["response_code"];
                    if (responseCode == ResponseCode::UPDATE) {
                        std::lock_guard<std::mutex> lock(m_Mutex);
                        for (auto& player : response["players"]) {
                            json position = player["position"];
                            uint32_t id = player["id"];
                            int x = position["x"];
                            int y = position["y"];
                            m_Players[id].SetSize(50, 100);
                            if (m_Players[id].GetId() == 0) {
                                m_Players[id].SetId(id);
                            }
                            m_Players[id].SetPosition(x, y);
                        }
                    } else if (responseCode == ResponseCode::CONNECTED) {
                        m_Id = response["id"];
                        std::cout << "Your id: " << m_Id << std::endl;
                    }
                } catch (const std::exception& e) {
                    std::cerr << "JSON parse error: " << e.what() << std::endl;
                }
            }
        } else if (result == 0) {
            std::cout << "Server closed connection." << std::endl;
            // Disconnect();
            break;
        } else {
            std::cout << "recv failed: " << WSAGetLastError() << std::endl;
            break;
        }
    }
    m_Running = false;
}

}