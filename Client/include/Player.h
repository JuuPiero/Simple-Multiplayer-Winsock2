#pragma once
#include "GameObject.h"
#include <iostream>
#include "Math/Vector2.h"
class Player : public JuuPiero::GameObject {
public:
    Player(int x, int y, int width, int height);
    Player() {}
    ~Player() = default;
    void Render() override;
    void Update(uint32_t deltaTime) override;
    void HandleInput(uint32_t deltaTime);
   
protected:
    // uint32_t m_Id;
    Vector2 m_Velocity;

    // static Player* s_Instance;
};