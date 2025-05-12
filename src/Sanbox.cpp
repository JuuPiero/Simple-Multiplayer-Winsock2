#include "Sanbox.h"
#include "Window/SDLNativeWindow.h"
#include "Player.h"
SDL_Renderer* Sanbox::s_Renderer = nullptr;
Sanbox::Sanbox(const JuuPiero::ApplicationProperties& props): Application(props)
{
    auto window = std::dynamic_pointer_cast<JuuPiero::SDLNativeWindow>(m_Window);
    s_Renderer = SDL_CreateRenderer(window->GetWindow(), -1, 0);

}

Sanbox::~Sanbox()
{
    SDL_DestroyRenderer(s_Renderer);
}

void Sanbox::Render() {
    SDL_SetRenderDrawColor(s_Renderer, 255, 0, 0, 255); // Đỏ
    SDL_RenderClear(s_Renderer);
}
void Sanbox::RenderUI() {
    
}

void Sanbox::Run() {
    uint32_t lastTime  = SDL_GetTicks();
    auto player = new Player(10, 10, 100, 100);
    while(!m_Window->ShouldClose()) {
        uint32_t currentTime = SDL_GetTicks();
        uint32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;
    
        Render();

        player->Update(deltaTime);
        // m_ImGuiLayer->BeginFrame();
        RenderUI();
        SDL_RenderPresent(s_Renderer);

        // m_ImGuiLayer->EndFrame();
        m_Window->Update();
    }
}