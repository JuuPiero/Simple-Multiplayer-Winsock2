#include "GameObject.h"

namespace JuuPiero {

GameObject::GameObject(int x, int y, int width, int height) {
    m_Rect = {x, y, width, height};
    m_Position = {x, y};
    m_Size = {width, height};
}

void GameObject::Render() {
    
}

void GameObject::Update(uint32_t deltaTime) {
    m_Rect = {m_Position.x, m_Position.y, m_Size.x, m_Size.y};
}


}