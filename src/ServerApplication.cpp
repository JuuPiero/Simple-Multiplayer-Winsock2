#include "ServerApplication.h"
#include "Window/SDLNativeWindow.h"
// #include "Utils.h"
#include <SDL2/SDL.h>

namespace JuuPiero {
ServerApplication::ServerApplication(JuuPiero::ApplicationProperties& props): Application(props) {
    // m_Window->CreateOpenGLContext();
    // m_ServerSocket = std::make_shared<JuuPiero::Server>();
}

ServerApplication::~ServerApplication() {
}


void ServerApplication::Run() {
    m_SocketServer.Run();
    // uint32_t lastTime = SDL_GetTicks();
    while(!m_Window->ShouldClose()) {
        // uint32_t currentTime = SDL_GetTicks();
        // uint32_t deltaTime = currentTime - lastTime;
        // lastTime = currentTime;
        // glClear(GL_COLOR_BUFFER_BIT);
        // glClearColor(1.0, 1.0, 1.0, 1.0);
        // m_ImGuiLayer->BeginFrame();
        Render();
        // player->Update(deltaTime);
        RenderUI();
        // SDL_RenderPresent(s_Renderer);
        // m_ImGuiLayer->EndFrame();
        m_Window->Update();
    }
}

void ServerApplication::Render() {
    
}
void ServerApplication::RenderUI() {
    
}
}