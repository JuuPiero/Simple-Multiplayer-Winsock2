#pragma once
#include "SDL2/SDL.h"
#include "Math/Vector2.h"
namespace JuuPiero {

class GameObject {
public:
    GameObject(int x, int y, int width, int height);
    ~GameObject() = default;
    virtual void Render();
    virtual void Update(uint32_t deltaTime);
protected:
    SDL_Rect m_Rect;

    Vector2 m_Position;
    Vector2 m_Size;    
};

// GameObject::GameObject(/* args */)
// {
// }

// GameObject::~GameObject()
// {
// }


}