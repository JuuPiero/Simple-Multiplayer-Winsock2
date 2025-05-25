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


void Application::LoadDotenv(const std::string& filepath)  {
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Xóa khoảng trắng ở đầu và cuối dòng
        line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
        line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), line.end());

        // Bỏ qua các dòng trống hoặc comment
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::istringstream iss(line);
        std::string key;
        if (std::getline(iss, key, '=')) {
            std::string value;
            if (!std::getline(iss, value)) {
                value = "";
            }

            // Xóa khoảng trắng ở đầu và cuối key và value
            key.erase(key.begin(), std::find_if(key.begin(), key.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }));
            key.erase(std::find_if(key.rbegin(), key.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
            }).base(), key.end());

            value.erase(value.begin(), std::find_if(value.begin(), value.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }));
            value.erase(std::find_if(value.rbegin(), value.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
            }).base(), value.end());

            // Đặt biến môi trường ngay cả khi giá trị rỗng
            #if defined(_WIN32) || defined(_WIN64)
                if (_putenv_s(key.c_str(), value.c_str()) != 0) {
                    std::cerr << "Error setting environment variable: " << key << std::endl;
                }
            #else
                if (setenv(key.c_str(), value.c_str(), 1) != 0) {
                    std::cerr << "Error setting environment variable: " << key << std::endl;
                }
            #endif
        }
    }

    file.close();
}

}