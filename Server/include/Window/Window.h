#pragma once
#include <string>
namespace JuuPiero {
class Application;

enum class WindowPlatform {
    NONE,
    SDL,
    GFLW
};

class Window {
private:
public:
    Window(int width, int height, std::string title, Application* app = nullptr): m_Width(width), m_Height(height), m_Title(title), m_App(app) {}
    ~Window() = default;
    
    virtual void Update() = 0;
    virtual void PollEvents() = 0;
    virtual bool ShouldClose() = 0;
    
    virtual void Initialize() = 0;

    virtual void CreateOpenGLContext() = 0;


protected:
    int m_Width;
    int m_Height;
    std::string m_Title;
    JuuPiero::Application* m_App;
};
}
