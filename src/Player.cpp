#include "Player.h"
#include "Sanbox.h"
Player::Player(int x, int y, int width, int height): GameObject(x, y, width, height) {

}

void Player::Render() {
    SDL_SetRenderDrawColor(Sanbox::GetRenderer(), 0, 255, 0, 255);
    SDL_RenderFillRect(Sanbox::GetRenderer(), &m_Rect);
}


void Player::Update(uint32_t deltaTime) {
    GameObject::Update(deltaTime);
    // int width, height;
    // SDL_GetWindowSize(window, &width, &height);
    if(m_Position.y + m_Size.y <  WINDOW_HEIGHT) {
        m_Position.y++;
    }

    Render();

}
