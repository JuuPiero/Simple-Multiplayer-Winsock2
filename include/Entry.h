#pragma once
#include "Utils.h"
#include "Application.h"

extern Shared<JuuPiero::Application> CreateApplication();


int main(int argc, char *argv[]) {
    auto app = CreateApplication();
   
    try {
        app->Run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n";
    }
  
    return 0;
}