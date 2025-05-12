#include "Window/GLFWNativeWindow.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace JuuPiero {
GLFWNativeWindow::GLFWNativeWindow(int width, int height, const char* title, Application* app): Window(width, height, title, app) {
    Initialize();
}

void GLFWNativeWindow::Initialize() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }
  

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
    
    if(m_Window == nullptr) {
        glfwTerminate();
        std::cerr << "fail to create window" << std::endl;
        return;
    }
    // CreateOpenGLContext();
   
    std::cout << "GLFW window" << std::endl;
}

void GLFWNativeWindow::CreateOpenGLContext() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1);
    if(!gladLoadGL(static_cast<GLADloadfunc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }
    glViewport(0, 0, m_Width, m_Height);
    glEnable(GL_DEPTH_TEST);
}

bool GLFWNativeWindow::ShouldClose() {
    return glfwWindowShouldClose(m_Window);
}

void GLFWNativeWindow::Update() {
    glfwSwapBuffers(m_Window);
    PollEvents();
}
void GLFWNativeWindow::PollEvents() {
    glfwPollEvents();
}

GLFWNativeWindow::~GLFWNativeWindow() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
    std::cout << "Destroying GLFW window" << std::endl;
}

}