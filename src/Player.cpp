#include "Player.h"

Player::Player(int x, int y, int width, int height): GameObject(x, y, width, height) {

}

void Player::Render() {
   
}


void Player::Update(uint32_t deltaTime) {
    GameObject::Update(deltaTime);
    Render();
}
