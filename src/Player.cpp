#include "Player.h"

Player::Player(int x, int y, int width, int height): GameObject(x, y, width, height) {

}

void Player::Render() {
    // SDL_SetRenderDrawColor(Sanbox::GetRenderer(), 0, 255, 0, 255);
    // SDL_RenderFillRect(Sanbox::GetRenderer(), &m_Rect);
}


void Player::Update(uint32_t deltaTime) {
    GameObject::Update(deltaTime);
    Render();
}
