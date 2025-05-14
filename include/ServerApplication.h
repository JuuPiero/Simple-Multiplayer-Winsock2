#pragma once
#include "Application.h"
#include <unordered_map>
// #include <SDL2/SDL.h>
// using namespace JuuPiero;

namespace JuuPiero {
class ServerApplication : public JuuPiero::Application {
public:
    ServerApplication(JuuPiero::ApplicationProperties& props);
    ~ServerApplication();
    void Run() override;
    void Render() override;
    void RenderUI() override;
    // inline static SDL_Renderer* GetRenderer() { return s_Renderer; }
    

protected:
    //ROOM
    // Shared<JuuPiero::Server> m_ServerSocket;
    // static SDL_Renderer* s_Renderer;
};

}
