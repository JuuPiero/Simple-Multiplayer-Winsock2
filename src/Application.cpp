#define STB_IMAGE_IMPLEMENTATION
#define GLAD_GL_IMPLEMENTATION
#define GLFW_INCLUDE_NONE




#include "Application.h"
#include "Window/Window.h"
#include "Window/GLFWNativeWindow.h"
#include "Window/SDLNativeWindow.h"

namespace JuuPiero {
Application::Application(const ApplicationProperties& props): m_Props(props) {
    switch(m_Props.Platform) {
        case WindowPlatform::GFLW: {
            m_Window = std::make_shared<GLFWNativeWindow>(m_Props.Width, m_Props.Height, m_Props.Title, this);
            break;
        }
        case WindowPlatform::SDL: {
            m_Window = std::make_shared<SDLNativeWindow>(m_Props.Width, m_Props.Height, m_Props.Title, this);
            break;
        }
        case WindowPlatform::NONE: {
            std::cerr << "Invalid window platform" << std::endl;
            return;
        }
        default: {
            std::cerr << "Invalid window platform" << std::endl;
            return;
        }
    }
    // m_ImGuiLayer = std::make_shared<ImGuiLayer>();
    // m_ImGuiLayer->Initialize();
    // ImGui_ImplGlfw_InitForOpenGL(m_Window->, true);
    // ImGui_ImplOpenGL3_Init("#version 330");
}

void Application::Run() {
    while(!m_Window->ShouldClose()) {
        // glClear(GL_COLOR_BUFFER_BIT);
        // glClearColor(1.0, 1.0, 1.0, 1.0);
        Render();
        // m_ImGuiLayer->BeginFrame();
        RenderUI();
        // m_ImGuiLayer->EndFrame();
        m_Window->Update();
    }
}

}