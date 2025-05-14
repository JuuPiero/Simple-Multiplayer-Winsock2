#include "ServerApplication.h"
#include "Window/SDLNativeWindow.h"
// #include "Utils.h"
#include <SDL2/SDL.h>

namespace JuuPiero {
ServerApplication::ServerApplication(JuuPiero::ApplicationProperties& props): Application(props) {
    // m_Window->CreateOpenGLContext();
    // players.emplace()
}


void ServerApplication::Run() {
  
    uint32_t lastTime = SDL_GetTicks();
    Server::GetInstance()->Run();

    while(!m_Window->ShouldClose()) {
        uint32_t currentTime = SDL_GetTicks();
        uint32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        m_Window->Update();
    }
}

void ServerApplication::Render() {
    
}
void ServerApplication::RenderUI() {
    
}

ServerApplication::~ServerApplication() {
    Server::GetInstance()->ShutDown();
}

}