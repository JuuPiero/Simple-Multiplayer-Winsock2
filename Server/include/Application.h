#pragma once
#include "Window/Window.h"
#include "Utils.h"

namespace JuuPiero {
struct ApplicationProperties {
    int Width, Height;
    std::string Title;
    WindowPlatform Platform;
};

class Application {
    friend class Window;
public:
    Application(const ApplicationProperties& props);
    virtual ~Application() = default;
    // virtual void Initialize();
    virtual void Run();
    virtual void Render() = 0;
    virtual void RenderUI() = 0;

    inline Shared<Window> GetNativeWindow() {
        return m_Window;
    }
    inline ApplicationProperties& GetProps() {
        return m_Props;
    }
    // virtual void Update();
protected:

    ApplicationProperties m_Props;
    Shared<Window> m_Window;
    // Shared<ImGuiLayer> m_ImGuiLayer;
};


}