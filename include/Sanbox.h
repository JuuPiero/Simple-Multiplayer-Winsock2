#pragma once
#include "Application.h"
#include <SDL2/SDL.h>
#include "Socket/Client.h"
#include "Player.h"
class Sanbox : public JuuPiero::Application {
public:
    Sanbox(const JuuPiero::ApplicationProperties& props);
    ~Sanbox();
    void Run() override;
    void Render() override;
    void RenderUI() override;

    inline static SDL_Renderer* GetRenderer() { return s_Renderer; }

protected:
    static SDL_Renderer* s_Renderer;

    // JuuPiero::Client m_SocketClient;
    Player m_Player = Player(10, 10, 50, 100);

};

