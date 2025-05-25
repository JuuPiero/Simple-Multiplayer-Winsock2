#pragma once
#include "SDL2/SDL.h"
#include "Math/Vector2.h"
namespace JuuPiero {

class GameObject {
public:
    GameObject(int x, int y, int width, int height);
    GameObject() {}

    ~GameObject() = default;
    virtual void Render();
    virtual void Update(uint32_t deltaTime);
    inline void SetPosition(const int& x, const int& y) {
        m_Position.x = x;
        m_Position.y = y;
    }
    inline void SetPosition(const Vector2& newPos) {
        m_Position = newPos;
    }

    inline void SetSize(const int& w, const int& h) {
        m_Size.x = w;
        m_Size.y = h;
    }

    inline void SetSize(const Vector2& newSize) {
        m_Size = newSize;
    }

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