#include "Window/SDLNativeWindow.h"
#include <glad/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include "Application.h"

namespace JuuPiero {
SDLNativeWindow::SDLNativeWindow(int width, int height, const char* title, Application* app): Window(width, height, title, app) {
    Initialize();
}

void SDLNativeWindow::Initialize() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize the SDL2 library\n";
        return ;
    }
    m_Window = SDL_CreateWindow(m_Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Width, m_Height, 0);
   
    // CreateOpenGLContext();

    std::cout << "SDL window" << std::endl;
}

void SDLNativeWindow::CreateOpenGLContext() {
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    SDL_GLContext context = SDL_GL_CreateContext(m_Window);
    SDL_GL_MakeCurrent(m_Window, context);
    if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)) {
        throw(std::string("Failed to initialize GLAD"));
    }
}

bool SDLNativeWindow::ShouldClose() {
    return !m_IsRunning;
}

void SDLNativeWindow::Update() {
    SDL_GL_SwapWindow(m_Window);
    PollEvents();
}
void SDLNativeWindow::PollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            m_IsRunning = false;
        }

        if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                int newWidth = event.window.data1;
                int newHeight = event.window.data2;
                auto props = m_App->GetProps();
                props.Width = newWidth;
                props.Height = newHeight; 
            }
        }
    }
}

SDLNativeWindow::~SDLNativeWindow() {
    // SDL_DestroyC 
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
    std::cout << "SDL window destroyed" << std::endl;
}

}