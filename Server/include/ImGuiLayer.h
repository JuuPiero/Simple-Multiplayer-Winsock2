#pragma once

namespace JuuPiero {
class ImGuiLayer {

public:
    ImGuiLayer();
    ~ImGuiLayer();
    void Initialize(); 
    void BeginFrame();
    void EndFrame();

};

}