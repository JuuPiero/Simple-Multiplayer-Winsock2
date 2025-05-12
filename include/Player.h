#pragma once
#include "GameObject.h"
#include <iostream>
#include "Math/Vector2.h"
class Player : public JuuPiero::GameObject {
public:
    Player(int x, int y, int width, int height);
    ~Player() = default;
    void Render() override;
    void Update(uint32_t deltaTime) override;

protected:
    Vector2 m_Velocity;
};