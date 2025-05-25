#pragma once
#include "Utils.h"
#include "Application.h"
#include "Socket/ServerSocket.h"

extern Shared<JuuPiero::Application> CreateApplication();


int main(int argc, char *argv[]) {
   JuuPiero::Application::LoadDotenv("./.env");


    const int PORT = atoi(getenv("PORT"));

    JuuPiero::ServerSocket server(getenv("SERVER_ADDRESS"));
    server.Listen(PORT, [PORT]() {
        std::cout << "Server " << getenv("SERVER_ADDRESS") << " listening on port " << PORT << std::endl;
    });
    
    std::string message = "";
    
    while (true)
    {
        std::cout << "Message to clients: ";
        std::getline(std::cin, message);
        server.Emit(message);
        // std::cin.ignore();
    }

    // auto app = CreateApplication();
    // app->Run();
    return 0;
}