#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <functional>
#include <mutex>
#include "Player.h"
#include <atomic>
namespace JuuPiero {

    class SocketClient {
    public:
        SocketClient();
        ~SocketClient();

        bool Connect(const std::string& ip, uint16_t port);
     
        void Emit(const std::string& message);
        void Disconnect();

        static SocketClient* GetInstance();

        inline const std::unordered_map<uint32_t, Player>& GetPlayers() const {
            return m_Players;
        }
        inline const uint32_t& GetId() {
            return m_Id;
        }
        inline void Lock() {
            std::lock_guard<std::mutex> lock(m_Mutex);
        }
    protected:
        void ReceiveLoop();

    protected:
        static SocketClient* s_Instance;
        uint32_t m_Id = 0;

        WSADATA m_WsaData;
        SOCKET m_Socket;
        std::thread m_ReceiveThread;
        // std::unordered_map<std::string, std::function<void(const std::string&)>> m_EventHandlers;
        std::mutex m_Mutex;
        std::atomic<bool> m_Running{false};


        std::unordered_map<uint32_t, Player> m_Players;
        std::string m_Leftover;
    };
}