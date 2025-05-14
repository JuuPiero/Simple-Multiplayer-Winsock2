#pragma once
#include "Utils.h"
#include "Application.h"
#include "Socket/ServerSocket.h"

extern Shared<JuuPiero::Application> CreateApplication();


int main(int argc, char *argv[]) {
    
    const int PORT = 8386;

    JuuPiero::ServerSocket server;
    server.Listen(PORT, []() {
        std::cout << "Server listening on port " << PORT << std::endl;
    }); // sub thread
    
    std::string message = "";
    
    while (true)
    {
        std::cout << "Message den tat ca: ";
        std::getline(std::cin, message);
        server.Emit(message);
        // std::cin.ignore();
    }

    // auto app = CreateApplication();
    // app->Run();
    return 0;
}