#pragma once
#include "Window/Window.h"
#include <string>
struct GLFWwindow;
namespace JuuPiero {

class GLFWNativeWindow : public Window {
public:
    GLFWNativeWindow(int width, int height, std::string title, Application* app = nullptr);
    ~GLFWNativeWindow();
    void Initialize() override;
    void PollEvents() override;
    bool ShouldClose() override;
    void Update() override;
    void CreateOpenGLContext() override;

    inline GLFWwindow* GetWindow() { return m_Window; }

protected:
    GLFWwindow* m_Window = nullptr;
};
}
