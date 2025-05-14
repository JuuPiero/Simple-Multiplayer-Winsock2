#pragma once
#include "Utils.h"
#include "Application.h"
#include "Socket/SocketClient.h"

extern Shared<JuuPiero::Application> CreateApplication();


int main(int argc, char *argv[]) {
    auto client = JuuPiero::SocketClient::GetInstance();

    if (client->Connect("127.0.0.1", 8386)) {
        auto app = CreateApplication();
        app->Run();
    }
    client->Disconnect();
    return 0;
}