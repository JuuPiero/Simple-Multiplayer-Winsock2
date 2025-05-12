#pragma once
#include "Utils.h"
#include "Application.h"

extern Shared<JuuPiero::Application> CreateApplication();


int main(int argc, char *argv[]) {
    auto app = CreateApplication();
    app->Run();
    return 0;
}