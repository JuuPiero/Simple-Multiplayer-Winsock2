#include "Sanbox.h"
#include "Window/SDLNativeWindow.h"
#include "Player.h"
#include "Socket/SocketClient.h"
#include "Socket/RequestCode.h"

#include "Utils.h"

using namespace JuuPiero;

SDL_Renderer* Sanbox::s_Renderer = nullptr;
Sanbox::Sanbox(const JuuPiero::ApplicationProperties& props): Application(props) {
    // m_SocketClient.SetApp(this);
    auto window = std::dynamic_pointer_cast<JuuPiero::SDLNativeWindow>(m_Window);
    s_Renderer = SDL_CreateRenderer(window->GetWindow(), -1, 0);
    
    // m_Player = Player(10, 10, 50, 100);
    // m_Players.push(m_Player);
}

Sanbox::~Sanbox()
{
    SDL_DestroyRenderer(s_Renderer);
}

void Sanbox::Render() {
    SDL_SetRenderDrawColor(s_Renderer, 31, 28, 44, 255); 
    SDL_RenderClear(s_Renderer);
}
void Sanbox::RenderUI() {
    
}

void Sanbox::Run() {

    const uint32_t FPS = 60;
    const uint32_t frameDelay = 1000 / FPS; // mỗi frame ~16ms

    uint32_t lastTime = SDL_GetTicks();

    while(!m_Window->ShouldClose()) {
        uint32_t currentTime = SDL_GetTicks();
        uint32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        Render();
        auto players = SocketClient::GetInstance()->GetPlayers();
        for (auto &p : players)
        {
            p.second.Update(deltaTime);
           
            if(p.first == SocketClient::GetInstance()->GetId()) {
                p.second.HandleInput(deltaTime);
            }
        }
        
        // SDL_PumpEvents();
        // const Uint8* keys = SDL_GetKeyboardState(nullptr);

        // m_ImGuiLayer->BeginFrame();

        RenderUI();
        SDL_RenderPresent(s_Renderer);
        // m_ImGuiLayer->EndFrame();

        uint32_t frameTime = SDL_GetTicks() - currentTime;

        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime); // chờ cho đủ 16ms nếu chạy quá nhanh
        }
        m_Window->Update();
    }
}