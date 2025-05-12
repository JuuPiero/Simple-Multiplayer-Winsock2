#pragma once

#include "Window/Window.h"
struct SDL_Window;
struct SDL_Renderer;

namespace JuuPiero {

class SDLNativeWindow : public Window {
public:
    SDLNativeWindow(int width, int height, const char* title, Application* app = nullptr);
    ~SDLNativeWindow();
    void Initialize() override;
    void PollEvents() override;
    bool ShouldClose() override;
    void Update() override;
    void CreateOpenGLContext() override;

    inline SDL_Window* GetWindow() { return m_Window; }
    // void CreateSimpleRenderer();

private:
    bool m_IsRunning = true;
    SDL_Window* m_Window;
 
    // SDL_GLContext m_Context;
};


}

