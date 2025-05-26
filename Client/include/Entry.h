#pragma once
#include "Utils.h"
#include "Application.h"
#include "Socket/SocketClient.h"

extern Shared<JuuPiero::Application> CreateApplication();


int main(int argc, char *argv[]) {
    JuuPiero::Application::LoadDotenv("./.env");
    const int PORT = atoi(getenv("PORT"));
    auto client = JuuPiero::SocketClient::GetInstance();
    if (client->Connect(getenv("SERVER_ADDRESS"), PORT)) {
        std::cout << "Connect to " << getenv("SERVER_ADDRESS") << ":" << PORT << std::endl;
        auto app = CreateApplication();
        app->Run();
    }
    client->Disconnect();
    return 0;
}