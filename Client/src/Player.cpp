#include "Player.h"
#include "Sanbox.h"
#include "Socket/RequestCode.h"
#include "Socket/SocketClient.h"
#include "Utils.h"


Player::Player(int x, int y, int width, int height): GameObject(x, y, width, height) {
  
    // m_Velocity = {3, 10};
}
void Player::SetId(uint32_t id) {
    m_Id = id;
    getDistinctColorFromInt(m_Id, &color.r, &color.g, &color.b);
    m_Velocity = {3, 10};
}

void Player::Render() {
   

    SDL_SetRenderDrawColor(Sanbox::GetRenderer(), color.r, color.g, color.b, 255);
    SDL_RenderFillRect(Sanbox::GetRenderer(), &m_Rect);
}

void Player::Update(uint32_t deltaTime) {
    GameObject::Update(deltaTime);
    Render();
  
}

void Player::HandleInput(uint32_t deltaTime) {

    SDL_PumpEvents();
    const Uint8* keys = SDL_GetKeyboardState(nullptr);
    auto prevX = m_Position.x;
    auto prevY = m_Position.y;

    if(m_Position.y + m_Size.y < WINDOW_HEIGHT) {
        m_Position.y += 5;
    }

    if (keys [SDL_SCANCODE_RIGHT]) {
        m_Position.x += m_Velocity.x;
        PrintLn(m_Position.x);
    }
    else if(keys[SDL_SCANCODE_LEFT]) {
        m_Position.x -= m_Velocity.x;
    }
    else if(keys[SDL_SCANCODE_SPACE]) {
        m_Position.y -= m_Velocity.y;
    }

    if(prevX != m_Position.x || prevY != m_Position.y) {
        // PrintLn("Update");
        json request;
        request["request_code"] = JuuPiero::RequestCode::MOVE;
        request["position"] = {
            {"x",  m_Position.x},
            {"y",  m_Position.y},
        };
        JuuPiero::SocketClient::GetInstance()->Emit(request.dump());
    }

}
